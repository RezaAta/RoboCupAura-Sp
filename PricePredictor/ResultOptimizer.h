#pragma once
#include <vector>

using namespace std;

class ResultOptimizer
{
public:
	ResultOptimizer();
	~ResultOptimizer();
	vector <double> predictions;
	vector <vector<double>> accuracies;
	double finalPrediction;

	//vector <vector<double>> 

	void SetPredictions();
	void SetAccuracies();
	void OptimizeFinalResult();

	double GetFinalResults();
};