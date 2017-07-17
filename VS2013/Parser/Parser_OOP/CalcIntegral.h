#pragma once

#include <iostream>
#include <vector>

class CalcIntegral
{
public:
	CalcIntegral(std::vector<double> data, std::vector<double> baseline_v,
		const double time_from, const double time_to, const double time_scale);

	CalcIntegral(std::vector<double> data, double baseline, std::vector<double> baseline_v,
		const double time_from, const double time_to, const double time_scale);
	
	CalcIntegral(std::vector<double> data, double baseline,
		const double time_from, const double time_to, const double time_scale);
	
	~CalcIntegral();

	double GetIntegrtal();
private:
	double integral;
	const int point_from;
	const int point_to;
};

