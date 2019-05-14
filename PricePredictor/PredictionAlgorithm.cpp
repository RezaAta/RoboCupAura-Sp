#include "stdafx.h"
#include "PredictionAlgorithm.h"
#include "ObjHandler.h"


PredictionAlgorithm::PredictionAlgorithm()
{
	MSEOfPastPrediction = 0;
	prediction = 0;
	ErrorSum = 0;
	errorOfLastPrediction = -1;
	previousRealPrice = 0;
	lowErrorDataSets.resize(1);
	mediumErrorDataSets.resize(1);
	highErrorDataSets.resize(1);
}


PredictionAlgorithm::~PredictionAlgorithm()
{
}


void PredictionAlgorithm::CalculateAccuracyOfPassedPrediction(double previousRealPrice)
{
	errorOfLastPrediction = abs(previousRealPrice - prediction);
	ErrorSum = ErrorSum + errorOfLastPrediction;
	//cout << realPrice << "\t" << prediction << "\t" << errorOfLastPrediction << "\n";
	if (prediction != 0)
		MSEOfPastPrediction = (errorOfLastPrediction)*(errorOfLastPrediction);
	//cout << "\n\t"<<this->errorOfLastPrediction;
}

double PredictionAlgorithm::GetPrediction()
{
	return prediction;
}

void PredictionAlgorithm::RunExtrapolation(vector<double> prices)
{
	previousRealPrice = ObjHandler::Instance()->dataSetProvider->lastPredictionRealPrice;

	if (previousRealPrice != -1)
	{
		CalculateAccuracyOfPassedPrediction(previousRealPrice);
		ClassifyData(30, 80, prices);
	}
}

void PredictionAlgorithm::ClassifyData(double lowerErrorBound, double upperErrorBound , vector<double> prices)
{
	if (errorOfLastPrediction <= lowerErrorBound)
	{
		if (lowErrorDataSets.back().empty() || prices[prices.size() - 3] == lowErrorDataSets.back().back() )
		{
			lowErrorDataSets.back().push_back(previousRealPrice);
		}
			
		else
		{
			lowErrorDataSets.resize(lowErrorDataSets.size() + 1);
			lowErrorDataSets.back().push_back(previousRealPrice);
		}
	}

	if (errorOfLastPrediction > lowerErrorBound && errorOfLastPrediction <= upperErrorBound)
	{
		if (mediumErrorDataSets.back().empty() || prices[prices.size() - 2] == mediumErrorDataSets.back().back())
		{
			mediumErrorDataSets.back().push_back(previousRealPrice);
		}

		else
		{
			mediumErrorDataSets.resize(mediumErrorDataSets.size() + 1);
			mediumErrorDataSets.back().push_back(previousRealPrice);
		}
	}

	if (errorOfLastPrediction > upperErrorBound)
	{
		if (highErrorDataSets.back().empty() || prices[prices.size() - 2] == highErrorDataSets.back().back())
		{
			highErrorDataSets.back().push_back(previousRealPrice);
		}

		else
		{
			highErrorDataSets.resize(highErrorDataSets.size() + 1);
			highErrorDataSets.back().push_back(previousRealPrice);
		}
	}
}

void PredictionAlgorithm::PrintClusters()
{
	for (int j = 0; j < lowErrorDataSets.size(); j++)
	{
		cout << "\n";

		for (int i = 0; i < lowErrorDataSets[j].size(); i++)
			cout << "\t" << lowErrorDataSets[j][i];
		
	}
	cout << "\nlowErrorDataSet Ended";

	for (int j = 0; j < mediumErrorDataSets.size(); j++)
	{
		cout << "\n";
		for (int i = 0; i < mediumErrorDataSets[j].size(); i++)
		{
			cout << "\t" << mediumErrorDataSets[j][i];
		}
	}
	cout << "\nmediumErrorDataSet Ended";

	for (int j = 0; j < highErrorDataSets.size(); j++)
	{
		cout << "\n";
		for (int i = 0; i < highErrorDataSets[j].size(); i++)
		{
			cout << "\t" << highErrorDataSets[j][i];
		}
	}
	cout << "\nhighErrorDataSet Ended";
}
