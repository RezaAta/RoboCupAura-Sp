#include "stdafx.h"
#include "TrendDetector.h"
#include "ObjHandler.h"

TrendDetector::TrendDetector()
{
	trendType = Random;
	slopeVarianceScale = -1;
	newtonLowCluster = { {} };
}

TrendDetector::~TrendDetector()
{
}

void TrendDetector::UpdateClusters()
{
	UpdateLowClusters();
	UpdateMediumClusters();
	UpdateHighClusters();
}

void TrendDetector::UpdateLowClusters()
{
	newtonLowCluster = ObjHandler::Instance()->newtonExtrapolation->lowErrorDataSets;
	splineLowCluster = ObjHandler::Instance()->splineExtrapolation->lowErrorDataSets;
	stirlingLowCluster = ObjHandler::Instance()->stirlingExtrapolation->lowErrorDataSets;
	regressionLowCluster = ObjHandler::Instance()->multipleLinearRegression->lowErrorDataSets;
}

void TrendDetector::UpdateMediumClusters()
{
}

void TrendDetector::UpdateHighClusters()
{
}

TrendTypes TrendDetector::DetectTrend(vector<double> dataSet)
{
	CalculateSlopeVariation(dataSet);
	return Random;
}

void TrendDetector::GetNewDataSet()
{
	prices = ObjHandler::Instance()->dataSetProvider->trend.prices;
}


double TrendDetector::CalculateSlope(double x1, double x2, double y1, double y2)
{
	return slope = (y2 - y1) / (x2 - x1);
}


void TrendDetector::CalculateVariance(vector<double> Data)
{
	variance = 0;
	double sum = 0;
	double mean = 0;
	for (int i = 0; i < Data.size() ; i++)
		sum = Data[i] + sum;
	
	mean = sum / Data.size();
	for (int i = 0; i < Data.size(); i++)
		variance = variance + (Data[i] - mean)*(Data[i] - mean) /Data.size();
}

void TrendDetector::FindVarianceThreshold()
{
	UpdateClusters();
	TrimClusters(newtonLowCluster,3);
	//TrimClusters(regressionLowCluster, 3);

	int numberOfElements = 0;
	for (int j = 0; j < newtonLowCluster.size(); j++)
		for (int i = 0; i < newtonLowCluster[j].size(); i++)
			numberOfElements++;

	//for (int j = 0; j < regressionLowCluster.size(); j++)
	//	for (int i = 0; i < regressionLowCluster[j].size(); i++)
	//		numberOfElements++;

	if (numberOfElements <20)
	{
		cout << "\nmore elements requierd in clusters, finding threshold canceled." << endl;
		return;
	}

	UpdateSlopeVarianceScale();
}

void TrendDetector::PrintCluster()
{
	for (int j = 0; j < newtonLowCluster.size(); j++)
	{
		cout << "\n";
		for (int i = 0; i < newtonLowCluster[j].size(); i++)
		{
			cout << "\t" << newtonLowCluster[j][i];
		}
	}
	cout << "\n" << "shit just ended." << endl;
}

	void TrendDetector::TrimClusters(vector<vector<double>> &clusters, int trimSize)
	{
		for (int j = 0; j < clusters.size(); j++)
		{
			if (clusters[j].size() <= trimSize) 
			{
				clusters[j].clear();
				clusters.erase(clusters.begin() + j);
				j--;
			}
		}
	}

	void TrendDetector::UpdateSlopeVarianceScale()
	{
		slopeVarianceScale = 0;

		CalculateSlopeVarianceScale(newtonLowCluster);
		cout << "\nslope variance scale:\t" << slopeVarianceScale;
		//CalculateSlopeVarianceScale(regressionLowCluster);

	}

	void TrendDetector::CalculateSlopeVarianceScale(vector<vector<double>> &cluster)
	{
		//TrimClusters(cluster, 3);

		for (int j = 0; j < cluster.size(); j++)
		{
			CalculateSlopeVariation(cluster[j]);
			slopeVarianceScale = (slopeVarianceScale + variance) / 2;
		}
	}

		void TrendDetector::CalculateSlopeVariation(vector<double> dataSet)
		{
			slopes.clear();

			for (int i = 0; i < dataSet.size()-1; i++)
				slopes.push_back(CalculateSlope(0, 1, dataSet[i], dataSet[i + 1]));
			
			CalculateVariance(slopes);
		}
