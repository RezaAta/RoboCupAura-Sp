#include "stdafx.h"
#include "DataProvider.h"


DataProvider::DataProvider(int lengthOfProvidedDataSet)
{
	this->lengthOfProvidedDataSet = lengthOfProvidedDataSet;
	numberOfDataSet = 0;
	beginingOfDataSet = 0;
	endOfDataSet = 0;
	lastPredictionRealPrice = -1;
	dataSetEnded = false;
}


DataProvider::~DataProvider()
{

}

void DataProvider::ProvideNewDataSet(vector<vector<double>> prices, int steps)
{
	
	if(endOfDataSet != 0)
		lastPredictionRealPrice = prices[endOfDataSet][4];
	
	
	beginingOfDataSet = steps * numberOfDataSet;
	endOfDataSet = beginingOfDataSet + lengthOfProvidedDataSet - 1;
	if (endOfDataSet >= prices.size() - 1)
		dataSetEnded = true;

	providedDataSet.clear();
	providedDataSet.resize(lengthOfProvidedDataSet);

	int i = 0;
	while(true)
	{
		if (i >= lengthOfProvidedDataSet)
			break;
		providedDataSet[i] = prices[beginingOfDataSet][0];// 4 is equal to the close price  in the prices vector
		i++;
		if (i >= lengthOfProvidedDataSet)
			break;
		providedDataSet[i] = prices[beginingOfDataSet][4];
		i++;
		if (i >= lengthOfProvidedDataSet)
			break;
		beginingOfDataSet++;
	}
	numberOfDataSet++;
}
