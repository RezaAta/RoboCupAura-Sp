#include "stdafx.h"
#include "CSVReader.h"
#include <iostream>


CSVReader::CSVReader()
{
}


CSVReader::~CSVReader()
{
}

void CSVReader::ReadStockDataFromFile(string address)
{
	ifstream file;
	file.open(address, ios::in);
	if (!file.is_open()) std::cout << "file could not be opened!\n";
	
	double open = 0, last = 0, high = 0, low = 0, volume = 0, close = 0;//i should put this in a new datastructure
	
	regex sregexOfNumbers("[^a-z^A-Z^,^\n^>^<^ ]+");
	
	ProcessCSV(file, sregexOfNumbers, open, last, high, low, close, volume);
}

void CSVReader::ProcessCSV(std::ifstream &file, std::regex &sregexOfNumbers, double &open, double &last, double &high, double &low, double &close, double &volume)
{
	vector<string> allMatches;

	for (int numberOfDay = 0; file.good(); numberOfDay++)
	{
		string line = "";
		getline(file, line, '\n');
		if (line.empty())
			continue;

		int pos = 0;

		allMatches = FindAllMatches(line, sregexOfNumbers);

		if (allMatches.empty() || allMatches.size() < 7)
		{
			cout << "\nthere was a problem when getting price info at day " << numberOfDay << ".";
			if (numberOfDay == 0)
				cout << " maybe u have header?(if u do ignore this massage)\n";

			numberOfDay--;
			continue;
		}

		open = stod(allMatches[1]);
		last = stod(allMatches[2]);
		high = stod(allMatches[3]);
		low = stod(allMatches[4]);
		close = stod(allMatches[5]);
		volume = stod(allMatches[6]);


		if (volume != 0) {
			stockPrices.resize(numberOfDay + 1);
			stockPrices[numberOfDay].push_back(open);
			stockPrices[numberOfDay].push_back(last);
			stockPrices[numberOfDay].push_back(high);
			stockPrices[numberOfDay].push_back(low);
			stockPrices[numberOfDay].push_back(close);
			stockPrices[numberOfDay].push_back(volume);
		}
		else {
			numberOfDay--;
		}
	}
	cout << "csv is processed\n";
}

vector<string> CSVReader::FindAllMatches(string &str, regex &reg)
{
	vector<string> allMatches(0);

	sregex_iterator currentMatch(str.begin(), str.end(), reg);
	sregex_iterator lastMatch;

	while (currentMatch != lastMatch)
	{
		smatch matches = *currentMatch;
		allMatches.push_back(matches.str(0));
		currentMatch++;
	}

	return allMatches;
}

void CSVReader::DisplayPriceData()
{
	for(int j = 1; j <= stockPrices.size() -1; j++)
	{
		for (int i = 0; i <= 5; i++)
		{
			cout << stockPrices[j][i] << "\t";
		}
		cout << '\n';
	}
}

