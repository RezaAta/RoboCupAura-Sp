#pragma once

using namespace std;

#include "NewtonExtrapolation.h"
#include "StirlingExtrapolation.h"
#include "SplineExtrapolation.h"
#include "MultipleLinearRegression.h"
#include "CSVReader.h"
#include "DataProvider.h"
#include "TrendDetector.h"
#include "Results.h"
#include "ResultOptimizer.h"
#include "Broker.h"

#include <vector>

class ObjHandler
{
public:

	static ObjHandler *Instance();

	ObjHandler();
	~ObjHandler();


	CSVReader *fileReader;
	NewtonExtrapolation *newtonExtrapolation;
	StirlingExtrapolation *stirlingExtrapolation;
	SplineExtrapolation *splineExtrapolation;
	MultipleLinearRegression *multipleLinearRegression;
	DataProvider *dataSetProvider;
	TrendDetector *trendDetector;
	Results *results;
	ResultOptimizer *resultOptimizer;
	Broker *broker;


	void RenewAllObjects();
};
