#pragma once

#include <fstream>
#include <string>
#include "ObjHandler.h"

using namespace std;

class PricePredictor
{
public:

};
void OutputDataEntry(int numberOfFiles, std::vector<std::string> &addresses, std::vector<std::string> &outputAddresses);
void SetDataEntry(std::string &inputAddress, int &numberOfFiles, std::vector<std::string> &addresses, std::vector<std::string> &outputAddresses);
void PrepareAllFiles(std::string &inputAddress, int &numberOfFiles, std::vector<std::string> &addresses, std::vector<std::string> &outputAddresses);
void SetErrorVarsAndPrediction(double &prediction, double &error, double realPrice, double &ErrorSum, double &maxErr);
void PrintErrorSums(double ErrorSum);
fstream OpenFileByAddress(std::string & inputAddress);
void WriteTextFile(string, string);

void RunAllPredictionAlgorithms(std::vector<double> &dataSet);
void PrepareAddress(string &);