#include "stdafx.h"
#include "ResultOptimizer.h"
#include "ObjHandler.h"


ResultOptimizer::ResultOptimizer()
{
	accuracies.resize(4);
	for (size_t j = 0; j < 4; j++)
	{
		for (size_t i = 0; i < 4; i++)
		{
			accuracies[j].push_back (0);
		}
	}
}

ResultOptimizer::~ResultOptimizer()
{
}

void ResultOptimizer::SetPredictions()
{
	predictions.clear();
	predictions.resize(2);

	predictions[0] = ObjHandler::Instance()->newtonExtrapolation->GetPrediction();
	//predictions[1] = ObjHandler::Instance()->splineExtrapolation->GetPrediction();
	predictions[1] = ObjHandler::Instance()->multipleLinearRegression->GetPrediction();
	//predictions[2] = ObjHandler::Instance()->stirlingExtrapolation->GetPrediction();
}

void ResultOptimizer::SetAccuracies()
{
	
	if (ObjHandler::Instance()->trendDetector->trendType == Linear)
	{
		accuracies[Linear][0] = ((accuracies[Linear][0])*(ObjHandler::Instance()->newtonExtrapolation->numberOfPredictionsMade) +
			(ObjHandler::Instance()->newtonExtrapolation->MSEOfPastPrediction)) /
			ObjHandler::Instance()->newtonExtrapolation->numberOfPredictionsMade + 1;
		//accuracies[Linear][1] = ((accuracies[Linear][1])*(ObjHandler::Instance()->splineExtrapolation->numberOfPredictionsMade) +
		//	(ObjHandler::Instance()->splineExtrapolation->MSEOfPastPrediction)) /
		//	ObjHandler::Instance()->splineExtrapolation->numberOfPredictionsMade + 1;
		//accuracies[Linear][2] = ((accuracies[Linear][2])*(ObjHandler::Instance()->stirlingExtrapolation->numberOfPredictionsMade) +
		//	(ObjHandler::Instance()->stirlingExtrapolation->MSEOfPastPrediction)) /
		//	ObjHandler::Instance()->stirlingExtrapolation->numberOfPredictionsMade + 1;
		accuracies[Linear][1] = ((accuracies[Linear][1])*(ObjHandler::Instance()->multipleLinearRegression->numberOfPredictionsMade) +
			(ObjHandler::Instance()->multipleLinearRegression->MSEOfPastPrediction)) /
			ObjHandler::Instance()->multipleLinearRegression->numberOfPredictionsMade + 1;
	}
	if (ObjHandler::Instance()->trendDetector->trendType == NonLinear)
	{
		accuracies[NonLinear][0] = ((accuracies[NonLinear][0])*(ObjHandler::Instance()->newtonExtrapolation->numberOfPredictionsMade)+
			(ObjHandler::Instance()->newtonExtrapolation->MSEOfPastPrediction)) /
			ObjHandler::Instance()->newtonExtrapolation->numberOfPredictionsMade+1;
		accuracies[NonLinear][1] = ((accuracies[NonLinear][1])*(ObjHandler::Instance()->splineExtrapolation->numberOfPredictionsMade) +
			(ObjHandler::Instance()->splineExtrapolation->MSEOfPastPrediction)) /
			ObjHandler::Instance()->splineExtrapolation->numberOfPredictionsMade + 1;
		accuracies[NonLinear][2] = ((accuracies[NonLinear][2])*(ObjHandler::Instance()->stirlingExtrapolation->numberOfPredictionsMade) +
			(ObjHandler::Instance()->stirlingExtrapolation->MSEOfPastPrediction)) /
			ObjHandler::Instance()->stirlingExtrapolation->numberOfPredictionsMade + 1;
		accuracies[NonLinear][3] = ((accuracies[NonLinear][3])*(ObjHandler::Instance()->multipleLinearRegression->numberOfPredictionsMade) +
			(ObjHandler::Instance()->multipleLinearRegression->MSEOfPastPrediction)) /
			ObjHandler::Instance()->multipleLinearRegression->numberOfPredictionsMade + 1;
	}
	if (ObjHandler::Instance()->trendDetector->trendType == Random)
	{
		accuracies[Random][0] = ((accuracies[NonLinear][0])*(ObjHandler::Instance()->newtonExtrapolation->numberOfPredictionsMade) +
			(ObjHandler::Instance()->newtonExtrapolation->MSEOfPastPrediction)) /
			ObjHandler::Instance()->newtonExtrapolation->numberOfPredictionsMade + 1;
		//accuracies[Random][1] = ((accuracies[NonLinear][1])*(ObjHandler::Instance()->splineExtrapolation->numberOfPredictionsMade) +
		//	(ObjHandler::Instance()->splineExtrapolation->MSEOfPastPrediction)) /
		//	ObjHandler::Instance()->splineExtrapolation->numberOfPredictionsMade + 1;
		accuracies[Random][1] = ((accuracies[NonLinear][1])*(ObjHandler::Instance()->multipleLinearRegression->numberOfPredictionsMade) +
			(ObjHandler::Instance()->multipleLinearRegression->MSEOfPastPrediction)) /
			ObjHandler::Instance()->multipleLinearRegression->numberOfPredictionsMade + 1;
		//accuracies[Random][2] = ((accuracies[NonLinear][2])*(ObjHandler::Instance()->stirlingExtrapolation->numberOfPredictionsMade) +
		//	(ObjHandler::Instance()->stirlingExtrapolation->MSEOfPastPrediction)) /
		//	ObjHandler::Instance()->stirlingExtrapolation->numberOfPredictionsMade + 1;
	}

}

void ResultOptimizer::OptimizeFinalResult()
{
	finalPrediction = 0;
	double totalWeight = 0;
	for (int i = 0; i < 2; i++)
	{
		totalWeight = totalWeight + 1/accuracies[ObjHandler::Instance()->trendDetector->trendType][i];
	}
	//cout << "\ntotal weight:" << totalWeight;
	if (totalWeight != 0)
	{
		for (int i = 0; i < 2; i++)
		{
			finalPrediction = finalPrediction + predictions[i] * ((1/accuracies[ObjHandler::Instance()->trendDetector->trendType][i]) / totalWeight);
			//cout << "\nfinal prediction:" << finalPrediction;
		}
	}
}

double ResultOptimizer::GetFinalResults()
{
	return finalPrediction;
}
