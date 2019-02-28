#include "stdafx.h"
#include "ObjectHandler.h"


ObjectHandler::ObjectHandler()
{
	fileReader = new CSVReader();
	newtonExtrapolation = new NewtonExtrapolation();
	stirlingExtrapolation = new StirlingExtrapolation();
	splineExtrapolation = new SplineExtrapolation();
	multipleLinearRegression = new MultipleLinearRegression();
	dataSetProvider = new DataProvider(2);
	trendDetector = new TrendDetector();
	results = new Results();
	resultOptimizer = new ResultOptimizer();
}

ObjectHandler *ObjectHandler::Instance()
{
	static ObjectHandler *s_instance = new ObjectHandler;
	return s_instance;
}

ObjectHandler::~ObjectHandler()
{
}

void ObjectHandler::RenewAllObjects()
{
	fileReader = new CSVReader();
	newtonExtrapolation = new NewtonExtrapolation();
	stirlingExtrapolation = new StirlingExtrapolation();
	splineExtrapolation = new SplineExtrapolation();
	multipleLinearRegression = new MultipleLinearRegression();
	dataSetProvider = new DataProvider(2);
	trendDetector = new TrendDetector();
	results = new Results();
	resultOptimizer = new ResultOptimizer();
}
