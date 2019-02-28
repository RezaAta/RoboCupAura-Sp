#pragma once
#include <ioStream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <codecvt>


using namespace std;

class CSVReader
{
public:
	CSVReader();
	~CSVReader();
	int numberOfColumns;
	string dataAddress;

	vector<vector<double>> stockPrices;

	void SaveStockData(string);

	void ProcessCSV(std::ifstream &file, std::string &line, std::vector<std::string> &allMatches, std::regex &sregexOfNumbers, double &open, double &last, double &high, double &low, double &close, double &volume);

	void DisplayPriceData();

	vector<string> SplitStringByChar(string, char);

private:
	vector<wstring> wFindAllMatches(wstring &,wregex &);
	vector<string> FindAllMatches(string &, regex &);

	string ws_to_utf8(wstring const&);
	wstring utf8_to_ws(string const&);

};
