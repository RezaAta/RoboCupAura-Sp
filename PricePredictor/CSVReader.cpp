#include "stdafx.h"
#include "CSVReader.h"


CSVReader::CSVReader()
{
}


CSVReader::~CSVReader()
{
}

void CSVReader::SaveStockData(string address)
{
	ifstream file;
	file.open(address, ios::in);
	if (!file.is_open()) cout << "file could not be opened!\n";
	
	double open = 0, last = 0, high = 0, low = 0, volume = 0, close = 0;
	string line;
	vector<string> dividedLine;

	regex sregexOfNumbers("[^a-z^A-Z^,^\n^>^<^ ]+");
	
	vector<string> allMatches;
	
	ProcessCSV(file, line, allMatches, sregexOfNumbers, open, last, high, low, close, volume);

}

void CSVReader::ProcessCSV(std::ifstream &file, std::string &line, std::vector<std::string> &allMatches, std::regex &sregexOfNumbers, double &open, double &last, double &high, double &low, double &close, double &volume)
{
	int numberOfDay = 0;

	for (; file.good(); numberOfDay++)
	{

		line = "";

		allMatches.clear();

		getline(file, line, '\n');

		//cout << line;
		if (line.empty())
			continue;
		int pos = 0;

		allMatches = FindAllMatches(line, sregexOfNumbers);

		if (allMatches.empty() || allMatches.size() < 7)
		{
			cout << "there was a problem at getting price info at day " << numberOfDay << ".";

			if (numberOfDay == 0)
				cout << " maybe u have header?(if u do ignore this massage)\n";
			numberOfDay--;
			continue;
		}

		else
		{
			//cout << allMatches.size();
			for (size_t i = 0; i < allMatches.size(); i++)
			{
				//cout << "shit";
				//allMatches[i] = ws_to_utf8(wAllMatches[i]);
				//cout <<"\n"<< allMatches[i];
			}
			//cout << allMatches[1];
			open = stod(allMatches[1]);
			last = stod(allMatches[2]);
			high = stod(allMatches[3]);
			low = stod(allMatches[4]);
			close = stod(allMatches[5]);
			volume = stod(allMatches[6]);
		}

		/*dividedLine = SplitStringByChar(line, ',');

		open =stod(dividedLine[1]);
		close = stod(dividedLine[2]);
		high = stod(dividedLine[3]);
		low = stod(dividedLine[4]);
		*/
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
		//for (int i = 0; i < 6; i++)
		//{
		//	if (stockPrices[numberOfDay][i] == 0)
		//		stockPrices[numberOfDay][i] = stockPrices[numberOfDay - 1][i];
		//}

	}
	cout << "csv is processed\n";
}

vector<string> CSVReader::SplitStringByChar(string str, char chr)
{
	vector<string> substrings;
	string substr;

	if (str.empty())
	{
		cout << "you gave me an empty string bro... what the hell am i supposed to do with an empty string???";
	}
	else 
	{
		while (true)
		{		
			size_t charPosition = str.find_first_of("[0-9]+",0);
			if (charPosition == string::npos)
			{
				substrings.emplace(substrings.end(), str);
				break;
			}
			substr = str.substr(0, charPosition);
			str = str.erase(0,charPosition + 1);
			
			substrings.emplace(substrings.end(),substr);
		}
	}
	return substrings;
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


vector<string> CSVReader::FindAllMatches(string &str, regex &reg)
{
	vector<string> allMatches(0);
	//wsmatch matches;

	sregex_iterator currentMatch(str.begin(), str.end(), reg);
	sregex_iterator lastMatch;
	while (currentMatch != lastMatch)
	{
		smatch matches = *currentMatch;
		//cout << matches.str() << "\n";
		//allMatches.resize(allMatches.size() + 1);
		allMatches.push_back(matches.str(0));
		currentMatch++;
	}

	return allMatches;
}