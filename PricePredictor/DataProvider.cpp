#include "stdafx.h"
#include "DataProvider.h"
#include "ObjHandler.h"


DataProvider::DataProvider(int lengthOfProvidedDataSet)
{
	spline.numberOfDataSet = 0;
	newton.numberOfDataSet = 0;
	regression.numberOfDataSet = 0;
	stirling.numberOfDataSet = 0;
	trend.numberOfDataSet = 0;

	newton.lastElementIndex = 0;
	stirling.lastElementIndex = 0;
	regression.lastElementIndex = 0;
	trend.lastElementIndex = 0;
	

	lastPredictionRealPrice = -1;
	allDataSetsEnded = false;
}

DataProvider::~DataProvider()
{

}

void DataProvider::ProvideAllNewDataSets()
{
	ProvideTrendDataSet();
	ProvideNewtonDataSet();
	ProvideRegressionDataSet();
	ProvideStirlingDataSet();
}
	void DataProvider::ProvideNewtonDataSet()
	{
		newton.length = 30;
		ProvideDataSet(ObjHandler::Instance()->fileReader->stockPrices, 1, 0 , newton);
	}

	void DataProvider::ProvideRegressionDataSet()
	{
		regression.length = 2;
		ProvideDataSet(ObjHandler::Instance()->fileReader->stockPrices,1, 28, regression);
	}

	void DataProvider::ProvideStirlingDataSet()
	{
		stirling.length = 10;
		ProvideDataSet(ObjHandler::Instance()->fileReader->stockPrices,1, 20, stirling);
	}

	void DataProvider::ProvideTrendDataSet()
	{
		trend.length = 30;
		ProvideDataSet(ObjHandler::Instance()->fileReader->stockPrices, 1, 0, trend);
	}

void DataProvider::ProvideDataSet(vector<vector<double>> prices, int steps, int shift, DataSet &dataSet)
{
	
	if (dataSet.lastElementIndex != 0)
		lastPredictionRealPrice = prices[dataSet.lastElementIndex][4];

	dataSet.firstElementIndex = (steps * dataSet.numberOfDataSet) + shift;
	dataSet.lastElementIndex = dataSet.firstElementIndex + dataSet.length - 1;

	if (dataSet.lastElementIndex >= prices.size() - 1)
		allDataSetsEnded = true;

	dataSet.prices.clear();
	dataSet.prices.resize(dataSet.length);
	
	for (int i = 0; !(i >= dataSet.length);)
	{
		//providedDataSet[i] = prices[beginingOfDataSet][0];// 4 is equal to the close price  in the prices vector
		//i++;
		//if (i >= lengthOfProvidedDataSet)
		//	break;
		dataSet.prices[i] = prices[dataSet.firstElementIndex][4];
		i++;
		if (i >= dataSet.length)
			break;
		dataSet.firstElementIndex++;
	}
	dataSet.numberOfDataSet++;
}


void DataProvider::ResetDataProvider()
{
	//numberOfDataSet = 0;
	lastPredictionRealPrice = -1;
}

DataSet::DataSet()
{
}
