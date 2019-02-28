#pragma once

#include <ioStream>
#include <fstream>
#include <string>
#include "ObjectHandler.h"

using namespace std;

class PricePredictor
{
public:

};

void ManualAddressInput(std::vector<std::string> &addresses);
void writeTextFile(string);

void RunAllPredictionAlgorithms(std::vector<double> &dataSet);
