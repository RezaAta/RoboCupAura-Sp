#include "stdafx.h"
#include "MultipleLinearRegression.h"
#include "ObjHandler.h"


MultipleLinearRegression::MultipleLinearRegression()
	:PredictionAlgorithm()
{
	alpha = 0.01;
	iterations = 500;
}


MultipleLinearRegression::~MultipleLinearRegression()
{
}


void MultipleLinearRegression::RunExtrapolation(vector<double> prices)
{
	PredictionAlgorithm::RunExtrapolation(prices);

	vector <double> x(prices.size());

	for (int i = 0; i < prices.size(); i++)
		x.push_back(i);
	
	LinearRegression linearRegression(x , prices, prices.size());
	linearRegression.train(this->alpha, this->iterations);

	this->prediction = linearRegression.predict(prices.size());
	numberOfPredictionsMade++;
}


void MultipleLinearRegression::OptimizeRegressionParameters(double error)
{
	OptimizeIterator(error, 200, 5);
	OptimizeALpha(error, 0.1, 0.001);
}


void MultipleLinearRegression::OptimizeIterator(double error , double baseSteps , double precision)
{
	cout << "\nEntered Iterator Optimizer";
	double newError = -1;
	double pastError = -1;
	double firstError = this->errorOfLastPrediction;
	double steps = baseSteps;
	bool stepsDirection = true;
	this->iterations = 100;
	
	while (true)
	{
		cout << "\n1";

		if ( newError!=-1)
			pastError = newError;
		
		RunExtrapolation(ObjHandler::Instance()->dataSetProvider->regression.prices);
		newError = this->errorOfLastPrediction;

		cout << "\n" << prediction;

		ChangeStepsDirection(newError, pastError, stepsDirection, steps);
		
		ProceedBySteps(this->iterations ,stepsDirection , steps);
		
		if (steps <= precision)
			break;

		cout << "\nNewError: " << newError;
		cout << "\nPastError: " << pastError;
	}
	cout << "\nFirstError: " << firstError;
	cout << "\nNewError: " << newError;
	cout << "\nNewiterations: " << this->iterations;

}

void MultipleLinearRegression::ChangeStepsDirection(double newError, double pastError, bool &iterationIncreasing, double &steps)
{
	if (newError >= pastError && pastError!= -1)
	{
		iterationIncreasing = !iterationIncreasing;
		
		steps = steps / 2;
		
		cout << "\nchangingDirection";
	}
}

void MultipleLinearRegression::OptimizeALpha(double error, double baseSteps, double precision)
{
	{
		cout << "\nEntered Alpha Optimizer";
		double newError = -1;
		double pastError = -1;
		double firstError = this->errorOfLastPrediction;
		double steps = baseSteps;
		bool stepsDirection = true;
		this->alpha = 0.1;

		while (true)
		{
			cout << "\n1";

			if (newError != -1)
				pastError = newError;

			RunExtrapolation(ObjHandler::Instance()->dataSetProvider->regression.prices);
			newError = this->errorOfLastPrediction;

			cout << "\n" << prediction;

			ChangeStepsDirection(newError, pastError, stepsDirection, steps);

			ProceedBySteps(this->alpha, stepsDirection, steps);

			if (steps <= precision)
				break;

			cout << "\nNewError: " << newError;
			cout << "\nPastError: " << pastError;
		}
		cout << "\nFirstError: " << firstError;
		cout << "\nNewError: " << newError;
		cout << "\nNewAlpha: " << this->alpha;

	}

}

void MultipleLinearRegression::ProceedBySteps(double &parameter, bool forward, double steps)
{
	if (forward)
		parameter = parameter + steps;

	else if (!forward)
		parameter = parameter - steps;

	cout <<"\nParameter: "<< parameter;
}
void MultipleLinearRegression::ProceedBySteps(int &parameter, bool forward, double steps)
{
	if (forward)
		parameter = parameter + steps;

	else if (!forward)
		parameter = parameter - steps;

	cout << "\nIterations: " << parameter;
}