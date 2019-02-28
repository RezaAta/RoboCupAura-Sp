#include "stdafx.h"
#include "Results.h"
#include "ObjectHandler.h"



Results::Results()
{
}


Results::~Results()
{
}

void Results::SetPredictions()
{
	AllPredictions[0][0] = ObjectHandler::Instance()->newtonExtrapolation->GetPrediction();
	AllPredictions[0][1] = ObjectHandler::Instance()->stirlingExtrapolation->GetPrediction();
	AllPredictions[0][2] = ObjectHandler::Instance()->splineExtrapolation->GetPrediction();
	AllPredictions[0][3] = ObjectHandler::Instance()->multipleLinearRegression->GetPrediction();				  
}

void Results::SetAccuracies(double[4])
{

}

double Results::GetFinalPrediction()
{
	return 0.0;
}

void Results::OptimizeFinalResult(double[2][4])
{

}

void Results::UpdateAccuracies(double[2][4])
{
}
