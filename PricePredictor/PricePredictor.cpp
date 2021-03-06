#include "stdafx.h"
#include "PricePredictor.h"

int main()
{
	string inputAddress;
	vector<double> dataSet;
	vector<string> addresses(11);
	vector<string> outputAddresses(11);
	int numberOfFiles;

	PrepareAllFiles(inputAddress, numberOfFiles, addresses, outputAddresses);

	for (int i = 0; i < numberOfFiles; i++)
	{
		string folderAddress = addresses[i];
		double prediction = 0;
		double ErrorSum = 0;
		double maxErr = 0;

		enum orderType{sell,buy};
		int order = sell;
		double balance = 1000;
		double equity;
		double priceDifPercentage = 0;

		ObjHandler::Instance()->fileReader->ReadStockDataFromFile(folderAddress);
		//ObjHandler::Instance()->fileReader->ReadStockDataFromFile("C:\\Users\\rezaa\\Desktop\\Prices\\PRICES.CSV");
		cout << "\nwait for prediction...\n";

		while (!ObjHandler::Instance()->dataSetProvider->allDataSetsEnded)
		{
			double error = 0;

			RunAllPredictionAlgorithms(dataSet);


			priceDifPercentage = 100 * (dataSet.back() - dataSet[dataSet.size() - 2])/dataSet.back();

			if (order == buy)
				balance = balance + balance * priceDifPercentage/100;
			
			cout << "\nbalance:\t" << balance;

			//ObjHandler::Instance()->trendDetector->FindVarianceThreshold();

			double realPrice = dataSet[dataSet.size() - 2];

			SetErrorVarsAndPrediction(prediction, error, realPrice, ErrorSum, maxErr);

			

			if (prediction <= dataSet.back())
				order = sell;
			else if (prediction > dataSet.back())
				order = buy;

			
		}

		//ObjHandler::Instance()->newtonExtrapolation->PrintClusters();
		//ObjHandler::Instance()->multipleLinearRegression->PrintClusters();

		cout << "\nmoving to next file\n";

		PrintErrorSums(ErrorSum);

		WriteTextFile("out" + to_string(i + 1), "C:\\AAIC2019 - StocksPredictionData\\");

		ObjHandler::Instance()->RenewAllObjects();
		//cout << ObjHandler::Instance()->dataSetProvider.numberOfDataSet << "\n";
		//cout << ObjHandler::Instance()->resultOptimizer.accuracies[ObjHandler::Instance()->trendDetector.trendType][0] << "\n";
		//cout << ObjHandler::Instance()->resultOptimizer.accuracies[ObjHandler::Instance()->trendDetector.trendType][1] << "\n";
		//cout << ObjHandler::Instance()->resultOptimizer.accuracies[ObjHandler::Instance()->trendDetector.trendType][2] << "\n";
		//cout << ObjHandler::Instance()->resultOptimizer.accuracies[ObjHandler::Instance()->trendDetector.trendType][3] << "\n";
	}
	return 0;
}


	void PrepareAllFiles(std::string &inputAddress, int &numberOfFiles, std::vector<std::string> &addresses, std::vector<std::string> &outputAddresses)
	{
		SetDataEntry(inputAddress, numberOfFiles, addresses, outputAddresses);

		//C:\Users\Prophet\Desktop\input.txt

		OutputDataEntry(numberOfFiles, addresses, outputAddresses);

		for (int i = 0; i < numberOfFiles; i++)
			PrepareAddress(addresses[i]);

		//system("DataPreProcessor\\DataPreProcessingEXE.exe");
	}

		void SetDataEntry(std::string &inputAddress, int &numberOfFiles, std::vector<std::string> &addresses, std::vector<std::string> &outputAddresses)
		{
			fstream file;

			file = OpenFileByAddress(inputAddress);

			for (int i = 0; file.good(); i++)
			{
				string line = "";

				if (i != 0)
					file.ignore();

				file >> line;

				if (i == 0)
					numberOfFiles = stoi(line);
				else if (i % 2 == 1)
					addresses[i / 2] = line;
				else if (i % 2 == 0)
					outputAddresses[i / 2 - 1] = line;

				if (i > numberOfFiles * 2)
					break;
			}	
		}

			fstream OpenFileByAddress(std::string & inputAddress)
		{
			fstream file;
			while (true)
			{
				cout << "please enter input file address:\n";
				cin >> inputAddress;
				PrepareAddress(inputAddress);
		

				file.open(inputAddress, ios::in);
				if (!file.is_open())
				{
					cout << "file could not be opened!\n";
					continue;
				}
				break;
			}
			return file;
		}

		void PrepareAddress(string &address)
		{
			int pos = 0;
			while (true)
			{
				pos = address.find("\\", pos);
				if (pos == -1)
					break;
				address.replace(pos, 1, "\\\\");
				pos = pos + 2;
			}
		}

		void OutputDataEntry(int numberOfFiles, std::vector<std::string> &addresses, std::vector<std::string> &outputAddresses)
		{
			ofstream out("DataPreProcessor\\input_addresses_address.txt");
			out << to_string(numberOfFiles) << "\n";

			for (int i = 0; i < numberOfFiles; i++)
				out << addresses[i] << "\n" << outputAddresses[i] << "\n";

			out.close();
		}


	void RunAllPredictionAlgorithms(std::vector<double> &dataSet)
	{
		ObjHandler::Instance()->dataSetProvider->ProvideAllNewDataSets();

		/*dataSet = ObjHandler::Instance()->dataSetProvider->trend.prices;
		ObjHandler::Instance()->trendDetector->DetectTrend(dataSet);*/

		dataSet = ObjHandler::Instance()->dataSetProvider->newton.prices;
		ObjHandler::Instance()->newtonExtrapolation->RunBackwardExtrapolation(dataSet);
		//ObjHandler::Instance()->splineExtrapolation->RunExtrapolation(dataSet);
		//dataSet = ObjHandler::Instance()->dataSetProvider->stirling.dataSet;
		//ObjHandler::Instance()->stirlingExtrapolation->RunExtrapolation(dataSet);

		dataSet = ObjHandler::Instance()->dataSetProvider->regression.prices;
		ObjHandler::Instance()->multipleLinearRegression->RunExtrapolation(dataSet);
		//if (ObjHandler::Instance()->dataSetProvider->lastPredictionRealPrice != -1)
		//	ObjHandler::Instance()->multipleLinearRegression->OptimizeRegressionParameters(ObjHandler::Instance()->multipleLinearRegression->errorOfLastPrediction);

		ObjHandler::Instance()->resultOptimizer->SetPredictions();
		ObjHandler::Instance()->resultOptimizer->SetAccuracies();
		ObjHandler::Instance()->resultOptimizer->OptimizeFinalResult();
	}

	void SetErrorVarsAndPrediction(double &prediction, double &error, double realPrice, double &ErrorSum, double &maxErr)
{
	if (prediction != 0)
		error = abs(realPrice - prediction);

	//cout <<"\t"<< realPrice << "\t" << realPrice - prediction << "\n";
	prediction = ObjHandler::Instance()->resultOptimizer->GetFinalResults();
	//cout << "pastprediction: " << error;
	//cout << "pastprediction: " << ObjHandler::Instance()->newtonExtrapolation->errorOfLastPrediction;

	ErrorSum = ErrorSum + error;

	if (error > maxErr)
		maxErr = error;
	//cout << "\n" << prediction;
}

	void PrintErrorSums(double ErrorSum)
{
	cout << "\nNewton Error Sum : " << ObjHandler::Instance()->newtonExtrapolation->ErrorSum;
	cout << "\nRegression Error Sum : " << ObjHandler::Instance()->multipleLinearRegression->ErrorSum;
	//cout << "\nStirling Error Sum : " << ObjHandler::Instance()->stirlingExtrapolation->ErrorSum;
	cout << "\nOptimized Error Sum : " << ErrorSum;
}

	void WriteTextFile(string fileName, string address)
	{
		std::ofstream out(address + fileName + ".txt");
		out << ObjHandler::Instance()->resultOptimizer->GetFinalResults();
		out.close();
	}
