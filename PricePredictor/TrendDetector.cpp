#include "stdafx.h"
#include "TrendDetector.h"
#include "ObjectHandler.h"



TrendDetector::TrendDetector()
{
	trendType = Random;
}


TrendDetector::~TrendDetector()
{
}

TrendTypes TrendDetector::DetectTrend(vector<double>)
{
	CalculateSlopeVariation();

	return Random;
}

void TrendDetector::GetNewDataSet()
{
	prices = ObjectHandler::Instance()->dataSetProvider->providedDataSet;
}

double TrendDetector::CalculateSlope(double x1,double x2,double y1,double y2)
{
	return slope = (y2 - y1)/(x2 - x1);
}

void TrendDetector::CalculateSlopeVariation()
{
	slopes.clear();

	for (int i = 0; i < prices.size()-1; i++)
	{
		slopes[i] = CalculateSlope(0, 1, prices[i], prices[i + 1]);
	}
	CalculateVariance(slopes);
}

void TrendDetector::CalculateVariance(vector<double> Data)
{
	variance = 0;
	double sum = 0;
	double mean = 0;
	for (int i = 0; i < Data.size() ; i++)
	{
		sum = Data[i] + sum;
	}
	mean = sum / Data.size();
	for (int i = 0; i < Data.size(); i++)
	{
		variance = variance + (Data[i] - mean)*(Data[i] - mean) /Data.size();
	}
}
