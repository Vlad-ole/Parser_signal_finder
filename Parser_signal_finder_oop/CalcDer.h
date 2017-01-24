#pragma once

#include <iostream>
#include <vector>

class CalcDer
{
public:
	CalcDer(std::vector<double> yv, const int param_n_points);
	~CalcDer();
	std::vector<double> GetDer();
private:
	void CalcDer::CalculateFilterCoeff(int points);

	std::vector<double> yv_der;
	static bool is_first_obj;
	static std::vector<double> C_i_der;
};

