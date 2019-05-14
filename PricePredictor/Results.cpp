#include "stdafx.h"
#include "Results.h"
#include "ObjHandler.h"



Results::Results()
{
}


Results::~Results()
{
}

void Results::SetPredictions()
{
	AllPredictions[0][0] = ObjHandler::Instance()->newtonExtrapolation->GetPrediction();
	AllPredictions[0][1] = ObjHandler::Instance()->stirlingExtrapolation->GetPrediction();
	AllPredictions[0][2] = ObjHandler::Instance()->splineExtrapolation->GetPrediction();
	AllPredictions[0][3] = ObjHandler::Instance()->multipleLinearRegression->GetPrediction();				  
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
