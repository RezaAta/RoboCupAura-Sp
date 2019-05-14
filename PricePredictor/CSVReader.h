#pragma once

#include <string>
#include <vector>
#include <regex>
#include <fstream>


using namespace std;

class CSVReader
{
public:
	CSVReader();
	~CSVReader();
	int numberOfColumns;
	string dataAddress;

	vector<vector<double>> stockPrices;

	void ReadStockDataFromFile(string);

	void ProcessCSV(std::ifstream &file, std::regex &sregexOfNumbers, double &open, double &last, double &high, double &low, double &close, double &volume);

	void DisplayPriceData();

private:
	vector<string> FindAllMatches(string &, regex &);

};
