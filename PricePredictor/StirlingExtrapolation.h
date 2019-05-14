#pragma once
#include "PredictionAlgorithm.h"

using namespace std;

class StirlingExtrapolation: public PredictionAlgorithm
{
	
public:
	StirlingExtrapolation();
	~StirlingExtrapolation();

	void RunExtrapolation(vector<double>) override;
};
