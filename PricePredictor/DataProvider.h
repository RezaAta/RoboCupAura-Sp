#pragma once

#include <vector>

using namespace std;

struct DataSet
{
	DataSet();

public:
	vector<double> prices;
	int length;
	int firstElementIndex;
	int lastElementIndex;
	int numberOfDataSet;

};

class DataProvider
{
public:
	DataProvider(int);
	~DataProvider();
	bool allDataSetsEnded;
	double lastPredictionRealPrice;

	bool newRequestAdded;

	DataSet newton;
	DataSet regression;
	DataSet stirling;
	DataSet trend;
	DataSet spline;
	
	void ProvideAllNewDataSets();
	void ProvideDataSet(vector<vector<double>>, int, int, DataSet &);
	void ProvideNewtonDataSet();
	void ProvideRegressionDataSet();
	void ProvideStirlingDataSet();
	void ProvideTrendDataSet();

	void ResetDataProvider();

};
