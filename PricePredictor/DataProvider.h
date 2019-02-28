#pragma once
#include <stdlib.h>
#include <ioStream>
#include <vector>

using namespace std;

class DataProvider
{
public:
	DataProvider(int);
	~DataProvider();
	bool dataSetEnded;
	int lengthOfProvidedDataSet;
	int beginingOfDataSet;
	int endOfDataSet;
	double lastPredictionRealPrice;

	bool newRequestAdded;
	int numberOfDataSet;
	vector<double> providedDataSet;

	void ProvideNewDataSet(vector<vector<double>>,int);
	
};

