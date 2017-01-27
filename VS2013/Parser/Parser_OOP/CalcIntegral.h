#pragma once

#include <iostream>
#include <vector>

class CalcIntegral
{
public:
	CalcIntegral(std::vector<double> data, std::vector<double> baseline,
		const double time_from, const double time_to, const double time_scale);
	~CalcIntegral();

	std::vector<double> GetDataIntegrtal();
	double GetIntegrtal();
private:
	std::vector<double> data_integrtal;
	double integral;
};

