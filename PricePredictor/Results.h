#pragma once


class Results
{
public:
	Results();
	~Results();
	
	double AllAccuracies[1][4];//first dimention is for classifying all item types next dimention is for total accuracy of each extrapolation.
	double AllPredictions[2][4];//first dimention is for predictions now and the passed time. the second dimention is 4 predictions of 4 extrapolations. 
	
	
	void SetPredictions();
	void SetAccuracies(double[4]);
	double GetFinalPrediction();
	
private:
	void OptimizeFinalResult(double[2][4]);
	void UpdateAccuracies(double[2][4]);
};

