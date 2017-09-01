#pragma once

#include <iostream>
#include <vector>

class CalcDoubleIntegral
{
public:
	CalcDoubleIntegral(std::vector<double> data, std::vector<double> baseline, const double time_scale);
	CalcDoubleIntegral(std::vector<double> data, double baseline, const double time_scale);
	CalcDoubleIntegral(std::vector<double> data, double baseline, const int point_from, const double time_scale);
	~CalcDoubleIntegral();

	std::vector<double> GetDataIntegrtal();
private:
	std::vector<double> data_integrtal;
};

