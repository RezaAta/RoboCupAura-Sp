#pragma once

#include "PredictionAlgorithm.h"

//using namespace std;

class NewtonExtrapolation : public PredictionAlgorithm
{
public:
	NewtonExtrapolation();
	~NewtonExtrapolation();

	double CalculateU(double, int);
	int fact(int);
	void RunForwardExtrapolation(vector<double>);
	void RunBackwardExtrapolation(vector<double>);
};