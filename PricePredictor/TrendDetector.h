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
	

	vector<vector<double>> splineDataSet, newtonDataSet, stirlingDataSet, regressionDataSet;

	TrendTypes DetectTrend(vector<double>);
	void GetNewDataSet();

private:
	double CalculateSlope(double, double, double, double);
	void CalculateSlopeVariation();
	void CalculateVariance(vector<double>);

	double slope;
	vector<double> slopes;
	double variance;

};

