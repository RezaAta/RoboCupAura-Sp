#include "stdafx.h"
#include "ObjHandler.h"


ObjHandler::ObjHandler()
{
	fileReader = new CSVReader();
	newtonExtrapolation = new NewtonExtrapolation();
	stirlingExtrapolation = new StirlingExtrapolation();
	splineExtrapolation = new SplineExtrapolation();
	multipleLinearRegression = new MultipleLinearRegression();
	dataSetProvider = new DataProvider(30);
	trendDetector = new TrendDetector();
	results = new Results();
	resultOptimizer = new ResultOptimizer();
}

ObjHandler *ObjHandler::Instance()
{
	static ObjHandler *s_instance = new ObjHandler;
	return s_instance;
}

ObjHandler::~ObjHandler()
{
}

void ObjHandler::RenewAllObjects()
{
	fileReader = new CSVReader();
	newtonExtrapolation = new NewtonExtrapolation();
	stirlingExtrapolation = new StirlingExtrapolation();
	splineExtrapolation = new SplineExtrapolation();
	multipleLinearRegression = new MultipleLinearRegression();
	dataSetProvider = new DataProvider(30);
	trendDetector = new TrendDetector();
	results = new Results();
	resultOptimizer = new ResultOptimizer();
}
