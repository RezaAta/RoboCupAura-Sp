#pragma once
#include "PredictionAlgorithm.h"

using namespace std;

class SplineExtrapolation : public PredictionAlgorithm
{
public:
	SplineExtrapolation();
	~SplineExtrapolation();

	void RunExtrapolation(vector<double>) override;
};