#pragma once
#include "LinearRegression.h"
#include "PredictionAlgorithm.h"

using namespace std;

class MultipleLinearRegression: public PredictionAlgorithm
{
public:
	MultipleLinearRegression();
	~MultipleLinearRegression();

	void RunExtrapolation(vector<double>) override;
	void OptimizeRegressionParameters(double);

private:
	void OptimizeIterator(double, double, double);
	void ChangeStepsDirection(double newError, double pastError, bool &iterationIncreasing, double &steps);
	void OptimizeALpha(double, double, double);

	double alpha;
	int iterations;
	void ProceedBySteps(double &,bool,double);
	void ProceedBySteps(int &, bool, double);

};