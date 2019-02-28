#include "stdafx.h"
#include "ResultOptimizer.h"
#include "ObjectHandler.h"


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

	predictions[0] = ObjectHandler::Instance()->newtonExtrapolation->GetPrediction();
	//predictions[1] = ObjectHandler::Instance()->splineExtrapolation->GetPrediction();
	predictions[1] = ObjectHandler::Instance()->multipleLinearRegression->GetPrediction();
	//predictions[2] = ObjectHandler::Instance()->stirlingExtrapolation->GetPrediction();
}

void ResultOptimizer::SetAccuracies()
{
	
	if (ObjectHandler::Instance()->trendDetector->trendType == Linear)
	{
		accuracies[Linear][0] = ((accuracies[Linear][0])*(ObjectHandler::Instance()->newtonExtrapolation->numberOfPredictionsMade) +
			(ObjectHandler::Instance()->newtonExtrapolation->MSEOfPastPrediction)) /
			ObjectHandler::Instance()->newtonExtrapolation->numberOfPredictionsMade + 1;
		//accuracies[Linear][1] = ((accuracies[Linear][1])*(ObjectHandler::Instance()->splineExtrapolation->numberOfPredictionsMade) +
		//	(ObjectHandler::Instance()->splineExtrapolation->MSEOfPastPrediction)) /
		//	ObjectHandler::Instance()->splineExtrapolation->numberOfPredictionsMade + 1;
		//accuracies[Linear][2] = ((accuracies[Linear][2])*(ObjectHandler::Instance()->stirlingExtrapolation->numberOfPredictionsMade) +
		//	(ObjectHandler::Instance()->stirlingExtrapolation->MSEOfPastPrediction)) /
		//	ObjectHandler::Instance()->stirlingExtrapolation->numberOfPredictionsMade + 1;
		accuracies[Linear][1] = ((accuracies[Linear][1])*(ObjectHandler::Instance()->multipleLinearRegression->numberOfPredictionsMade) +
			(ObjectHandler::Instance()->multipleLinearRegression->MSEOfPastPrediction)) /
			ObjectHandler::Instance()->multipleLinearRegression->numberOfPredictionsMade + 1;
	}
	if (ObjectHandler::Instance()->trendDetector->trendType == NonLinear)
	{
		accuracies[NonLinear][0] = ((accuracies[NonLinear][0])*(ObjectHandler::Instance()->newtonExtrapolation->numberOfPredictionsMade)+
			(ObjectHandler::Instance()->newtonExtrapolation->MSEOfPastPrediction)) /
			ObjectHandler::Instance()->newtonExtrapolation->numberOfPredictionsMade+1;
		accuracies[NonLinear][1] = ((accuracies[NonLinear][1])*(ObjectHandler::Instance()->splineExtrapolation->numberOfPredictionsMade) +
			(ObjectHandler::Instance()->splineExtrapolation->MSEOfPastPrediction)) /
			ObjectHandler::Instance()->splineExtrapolation->numberOfPredictionsMade + 1;
		accuracies[NonLinear][2] = ((accuracies[NonLinear][2])*(ObjectHandler::Instance()->stirlingExtrapolation->numberOfPredictionsMade) +
			(ObjectHandler::Instance()->stirlingExtrapolation->MSEOfPastPrediction)) /
			ObjectHandler::Instance()->stirlingExtrapolation->numberOfPredictionsMade + 1;
		accuracies[NonLinear][3] = ((accuracies[NonLinear][3])*(ObjectHandler::Instance()->multipleLinearRegression->numberOfPredictionsMade) +
			(ObjectHandler::Instance()->multipleLinearRegression->MSEOfPastPrediction)) /
			ObjectHandler::Instance()->multipleLinearRegression->numberOfPredictionsMade + 1;
	}
	if (ObjectHandler::Instance()->trendDetector->trendType == Random)
	{
		accuracies[Random][0] = ((accuracies[NonLinear][0])*(ObjectHandler::Instance()->newtonExtrapolation->numberOfPredictionsMade) +
			(ObjectHandler::Instance()->newtonExtrapolation->MSEOfPastPrediction)) /
			ObjectHandler::Instance()->newtonExtrapolation->numberOfPredictionsMade + 1;
		//accuracies[Random][1] = ((accuracies[NonLinear][1])*(ObjectHandler::Instance()->splineExtrapolation->numberOfPredictionsMade) +
		//	(ObjectHandler::Instance()->splineExtrapolation->MSEOfPastPrediction)) /
		//	ObjectHandler::Instance()->splineExtrapolation->numberOfPredictionsMade + 1;
		accuracies[Random][1] = ((accuracies[NonLinear][1])*(ObjectHandler::Instance()->multipleLinearRegression->numberOfPredictionsMade) +
			(ObjectHandler::Instance()->multipleLinearRegression->MSEOfPastPrediction)) /
			ObjectHandler::Instance()->multipleLinearRegression->numberOfPredictionsMade + 1;
		//accuracies[Random][2] = ((accuracies[NonLinear][2])*(ObjectHandler::Instance()->stirlingExtrapolation->numberOfPredictionsMade) +
		//	(ObjectHandler::Instance()->stirlingExtrapolation->MSEOfPastPrediction)) /
		//	ObjectHandler::Instance()->stirlingExtrapolation->numberOfPredictionsMade + 1;
	}

}

void ResultOptimizer::OptimizeFinalResult()
{
	finalPrediction = 0;
	double totalWeight = 0;
	for (int i = 0; i < 2; i++)
	{
		totalWeight = totalWeight + 1/accuracies[ObjectHandler::Instance()->trendDetector->trendType][i];
	}
	//cout << "\ntotal weight:" << totalWeight;
	if (totalWeight != 0)
	{
		for (int i = 0; i < 2; i++)
		{
			finalPrediction = finalPrediction + predictions[i] * ((1/accuracies[ObjectHandler::Instance()->trendDetector->trendType][i]) / totalWeight);
			//cout << "\nfinal prediction:" << finalPrediction;
		}

	}
}

double ResultOptimizer::GetFinalResults()
{
	return finalPrediction;
}
