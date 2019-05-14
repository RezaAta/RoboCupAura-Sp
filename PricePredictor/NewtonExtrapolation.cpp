#include "stdafx.h"
#include "NewtonExtrapolation.h"
#include "ObjHandler.h"

NewtonExtrapolation::NewtonExtrapolation()
	:PredictionAlgorithm()
{
}


NewtonExtrapolation::~NewtonExtrapolation()
{
}

// newton forward interpolation 
// calculating u mentioned in the formula 
double NewtonExtrapolation::CalculateU(double u, int n)
{
	double temp = u;
	for (int i = 1; i < n; i++)
		temp = temp * (u - i);
	return temp;
}

// calculating factorial of given number n 
int NewtonExtrapolation::fact(int n)
{
	int f = 1;
	for (int i = 2; i <= n; i++)
		f *= i;
	return f;
}

void NewtonExtrapolation::RunForwardExtrapolation(vector<double> prices)
{

	PredictionAlgorithm::RunExtrapolation(prices);

	// Number of values given
	int n = ObjHandler::Instance()->dataSetProvider->newton.length;

	// y[][] is used for difference table
	// with y[][0] used for input
	vector<vector<double>> y;
	y.resize(prices.size());
	for (int i = 0; i < prices.size(); i++)
	{
		y[i].resize(prices.size());
		y[i][0] = prices[i];
	}
	//for (int i = 0; i < prices.size(); i++)
	//{
	//	cout <<"\n\t" <<y[i][0] << "\n";
	//}
	// Calculating the forward difference 
	// table 
	for (int i = 1; i < n; i++) 
	{
		for (int j = 0; j < n - i; j++)
			y[j][i] = y[j + 1][i - 1] - y[j][i - 1];
	}

	// Value to interpolate at 
	double value = prices.size();

	// initializing u and sum 
	double sum = y[0][0];
	double u = (value);
	for (int i = 1; i < n; i++) 
	{
		sum = sum + (CalculateU(u, i) * y[0][i]) /fact(i);
	}

	prediction = sum;
	numberOfPredictionsMade++;
}

void NewtonExtrapolation::RunBackwardExtrapolation(vector<double> prices)
{

	PredictionAlgorithm::RunExtrapolation(prices);

	// Number of values given 
	int n = ObjHandler::Instance()->dataSetProvider->newton.length;

	// y[][] is used for difference table
	// with y[][0] used for input
	vector<double> x;
	for (int i = 0; i < prices.size(); i++)
	{
		x.push_back(i);
	}
	
	vector<vector<double>> y;
	y.resize(prices.size());
	for (int i = 0; i < prices.size(); i++)
	{
		y[i].resize(prices.size());
		y[i][0] = prices[i];
	}

	// Calculating the backward difference 
	// table 
	for (int i = 1; i < n; i++) {
		for (int j = n - 1; j >= i; j--)
			y[j][i] = y[j][i - 1] - y[j - 1][i - 1];
	}

	// Value to interpolate at 
	double value = prices.size();

	// Initializing u and sum 
	double sum = y[n - 1][0];
	double u = (value - x[n - 1]) / (x[1] - x[0]);
	for (int i = 1; i < n; i++) {
		sum = sum + (CalculateU(u, i) * y[n - 1][i]) /
			fact(i);
	}

	prediction = sum;
	this->numberOfPredictionsMade++;
}

