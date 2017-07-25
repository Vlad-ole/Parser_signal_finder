#pragma once

#include <iostream>
#include <vector>

class CalcDoubleIntegralCalib
{
public:
	CalcDoubleIntegralCalib(std::vector<double> data, std::vector< std::pair<int, int> >& pair_vec, double HORIZ_INTERVAL);
	~CalcDoubleIntegralCalib();

	std::vector<double> GetDoubleIntegralVec();
private:
	std::vector<double> double_integral_vec;
};

