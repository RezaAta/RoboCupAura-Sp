#ifndef ML_LINEARREGRESSION_H
#define ML_LINEARREGRESSION_H
#include <vector>


using namespace std;

class LinearRegression {

public:

	vector<double> x;

	vector<double> y;

	int m;

	double *theta;

	LinearRegression(vector<double> x, vector<double> y, int m);

	void train(double alpha, int iterations);


	double predict(double x);

private:

	static double compute_cost(vector<double> x, vector<double> y, double theta[], int m);


	static double h(double x, double theta[]);


	static double *calculate_predictions(vector<double> x, double theta[], int m);

	static double *gradient_descent(vector<double> x, vector<double> y, double alpha, int iters, double *J, int m);

};


#endif //ML_LINEARREGRESSION_H
