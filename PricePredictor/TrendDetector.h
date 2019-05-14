#pragma once
#include <vector>

using namespace std;

enum TrendTypes { Linear, NonLinear, Random };

class TrendDetector
{
public:
	TrendDetector();
	~TrendDetector();

	TrendTypes trendType;
	vector<double> prices;
	int beginingOfTrend, endOfTrend;
	double slopeVariation;
	
	vector<vector<double>> splineLowCluster, newtonLowCluster, stirlingLowCluster, regressionLowCluster;
	
	TrendTypes DetectTrend(vector<double>);

	void FindVarianceThreshold();
	void UpdateClusters();

	void GetNewDataSet();
	

	void PrintCluster();

private:
	void UpdateLowClusters();
	void UpdateMediumClusters();
	void UpdateHighClusters();


	double CalculateSlope(double, double, double, double);
	void CalculateSlopeVariation(vector<double>);
	void CalculateVariance(vector<double>);
	void TrimClusters(vector<vector<double>>&, int);


	double slopeVarianceScale;
	void UpdateSlopeVarianceScale();
	void CalculateSlopeVarianceScale(vector<vector<double>> &);

	double slope;
	vector<double> slopes;
	double variance;

};

