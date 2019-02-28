#include "stdafx.h"
#include "StirlingExtrapolation.h"
#include "ObjectHandler.h"


StirlingExtrapolation::StirlingExtrapolation()
	:PredictionAlgorithm()
{
}

StirlingExtrapolation::~StirlingExtrapolation()
{
}


void StirlingExtrapolation::RunExtrapolation(vector<double> prices)
{
	PredictionAlgorithm::RunExtrapolation(prices);

	//vector<double> x;
	vector<double> fx (prices);

	for (int i = 0; i < fx.size(); i++)
	{
		fx[i] = fx[i] / 10000;
	}
	double x1 = prices.size(); // equals to the next index after last index of prices.
	int n = prices.size()-1;
	
		double h, a, u, y1 = 0, N1 = 1, d = 1,
			N2 = 1, d2 = 1, temp1 = 1, temp2 = 1,
			k = 1, l = 1;
		vector <vector<double>> delta(n);
		for (int i = 0; i < n; i++)
		{
			delta[i].resize(n - 1);
		}

		int i, j, s;
		h = 1;
		s = floor(n / 2);
		a = s;
		u = (x1 - a)/h;

		// Preparing the forward difference 
		// table 
		for (i = 0; i < n - 1; ++i) {
			delta[i][0]=fx[i + 1] - fx[i];
		}
		for (i = 1; i < n - 1; ++i) {
			for (j = 0; j < n - i - 1; ++j) {
				delta[j][i] = delta[j + 1][i - 1] - delta[j][i - 1];
			}
		}

		// Calculating f(x) using the Stirling  
		// formula 
		y1 = fx[s];

		for (i = 1; i <= n - 1; ++i) {
			if (i % 2 != 0) 
			{
				if (k != 2) 
				{
					temp1 *= (pow(u, k) - pow((k - 1), 2));
				}
				else 
				{
					temp1 *= (pow(u, 2) - pow((k - 1), 2));
				}
				++k;
				d *= i;
				s = floor((n - i) / 2);
				y1 += (temp1 / (2 * d)) * (delta[s][i - 1] + delta[s - 1][i - 1]);
			}
			else 
			{
				temp2 *= (pow(u, 2) - pow((l - 1), 2));
				++l;
				d *= i;
				s = floor((n - i) / 2);
				y1 += (temp2 / (d)) * (delta[s][i - 1]);
			}
		}

		prediction = y1*10000;
}