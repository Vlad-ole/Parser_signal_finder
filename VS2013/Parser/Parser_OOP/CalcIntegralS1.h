#pragma once

#include <iostream>
#include <vector>

class CalcIntegralS1
{
public:
	CalcIntegralS1(std::vector<double>& data, double time_s1_left, double time_s1_right, int point_s2_left,
		double HORIZ_INTERVAL, std::vector<int>& peak_position);
	~CalcIntegralS1();

	double GetIntegrtal();
private:
	double integral_s1_all_peaks;
};

