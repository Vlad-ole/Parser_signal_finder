#pragma once

#include <iostream>
#include <vector>

class CalcDer
{
public:
	CalcDer(std::vector<double> yv, const int param_n_points);
	~CalcDer();
	std::vector<double> GetDer();
	//std::vector<double> GetSmooth();
private:
	void CalcDer::CalculateCoeffDer(int points);
	//void CalcDer::CalculateCoeffSmooth(int points);

	std::vector<double> yv_der;
	std::vector<double> yv_smooth;
	static bool is_first_obj;
	static std::vector<double> C_i_der;
	//static std::vector<double> C_i_smooth;
};

