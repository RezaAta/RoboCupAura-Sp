#pragma once
#include <vector>
#include <iostream>

using namespace std;

class PredictionAlgorithm
{
public:
	PredictionAlgorithm();
	~PredictionAlgorithm();

	double prediction;
	double MSEOfPastPrediction;
	int numberOfPredictionsMade;
	double ErrorSum;
	bool serie;
	double previousRealPrice;
	double errorOfLastPrediction;

	vector <vector<double>> lowErrorDataSets;
	vector <vector<double>> mediumErrorDataSets;
	vector <vector<double>> highErrorDataSets;

	void CalculateAccuracyOfPassedPrediction(double);
	double GetPrediction();
	virtual void RunExtrapolation(vector<double>);
	
	void ClassifyData(double, double , vector<double>);
	void PrintClusters();
	
};