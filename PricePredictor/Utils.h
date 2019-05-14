#pragma once
#ifndef ML_UTILS_H
#define ML_UTILS_H

#include <vector>

using namespace std;

class Utils {

public:
	static double array_sum(double arr[], int len, vector<double> multiplication);
	static double array_sum(double arr[], int len);

	static double *array_pow(double arr[], int len, int power);

	static double *array_multiplication(double arr1[], vector<double> arr2, int len);

	static double *array_diff(double arr1[], vector<double> arr2, int len);

};

#endif //ML_UTILS_H
