#include "CalcDer.h"

using namespace std;

bool CalcDer::is_first_obj = true;
std::vector<double> CalcDer::C_i_der(0);
//std::vector<double> CalcDer::C_i_smooth(0);

CalcDer::CalcDer(std::vector<double> yv, const int param_n_points)
{
	const int n_points = yv.size();
	yv_der.resize(n_points);
	//yv_smooth.resize(n_points);

	if (is_first_obj)
	{
		is_first_obj = false;
		CalculateCoeffDer(param_n_points);
		//CalculateCoeffSmooth(param_n_points * 5);
	}

	const int point_half = (param_n_points - 1) / 2.0;

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

			//value = 0;
			//for (int j = 0; j < C_i_smooth.size(); j++)
			//{
			//	value += C_i_smooth[j] * yv[i - point_half + j];
			//}
			//yv_smooth[i] = value;


		}

	}

}


CalcDer::~CalcDer()
{
}

std::vector<double> CalcDer::GetDer()
{
	return yv_der;
}

//std::vector<double> CalcDer::GetSmooth()
//{
//	return yv_smooth;
//}

void CalcDer::CalculateCoeffDer(int points)
{
	//cout << endl << "start Calculate filter coefficients" << endl;

	//SavitzkyЦGolay filter
	//order = 3

	//vector<double> C_i_der;
	int m = points;//

				   //посчитать коэффициенты  C_i
	for (int i = (1 - m) / 2.0; i <= (m - 1) / 2.0; i++)
	{
		double numerator = 5 * (3 * pow(m, 4.0) - 18 * pow(m, 2.0) + 31)*i - 28 * (3 * pow(m, 2.0) - 7)*pow(i, 3.0);
		double denominator = m * (pow(m, 2.0) - 1) * (3 * pow(m, 4.0) - 39 * pow(m, 2.0) + 108) / 15.0;
		C_i_der.push_back(numerator / denominator);
	}
	//cout << endl << "stop Calculate filter coefficients" << endl;
}

//void CalcDer::CalculateCoeffSmooth(int points)
//{
//	int m = points;//
//
//	//посчитать коэффициенты  C_i
//	for (int i = (1 - m) / 2.0; i <= (m - 1) / 2.0; i++)
//	{
//		double numerator = (3 * pow(m, 2.0) - 7 - 20 * pow(i, 2.0)) / 4.0;
//		double denominator = m * (pow(m, 2.0) - 4) / 3.0;
//		C_i_smooth.push_back(numerator / denominator);
//	}
//}
