#include <iostream>
#include <vector>

#include "Golay_filter.h"

using namespace std;

//Calculate Filter Coeff for (Savitzky–Golay filter)
vector<double> CalculateFilterCoeff(int points)
{
	//cout << endl << "start Calculate filter coefficients" << endl;

	//Savitzky–Golay filter
	//order = 3

	vector<double> C_i_der;
	int m = points;//

	//ïîñ÷èòàòü êîıôôèöèåíòû  C_i
	for (int i = (1 - m) / 2.0; i <= (m - 1) / 2.0; i++)
	{
		double numerator = 5 * (3 * pow(m, 4.0) - 18 * pow(m, 2.0) + 31)*i - 28 * (3 * pow(m, 2.0) - 7)*pow(i, 3.0);
		double denominator = m * (pow(m, 2.0) - 1) * (3 * pow(m, 4.0) - 39 * pow(m, 2.0) + 108) / 15.0;
		C_i_der.push_back(numerator / denominator);
	}
	//cout << endl << "stop Calculate filter coefficients" << endl;
	return C_i_der;
}



//Calculate Derivative (Savitzky–Golay filter)
vector<double> CalculateDerivative(vector<double> yv, int points)
{
	//cout << endl << "start Calculate Derivatives" << endl;

	vector<double> C_i_der = CalculateFilterCoeff(points);


	vector<double> yv_der;
	const int point_half = (points - 1) / 2.0;
	yv_der.resize(yv.size());

#pragma omp parallel for num_threads(4)
	for (int i = 0; i < yv.size(); i++)
	{

		if (i < point_half || i >(yv.size() - point_half - 1))
		{
			yv_der[i] = 0;
		}
		else
		{
			double value = 0;
			for (int j = 0; j < C_i_der.size(); j++)
			{
				value += C_i_der[j] * yv[i - point_half + j];
			}
			yv_der[i] = value;

		}

	}

	//cout << endl << "stop Calculate Derivatives" << endl;

	return yv_der;
}