#pragma once

#include <iostream>
#include <vector>

class CalcBaseline
{
public:
	CalcBaseline(std::vector<double> yv);
	~CalcBaseline();

	double GetBaseline();
	std::vector<double>& GetBaselineVec();
private:
	double baseline;
	std::vector<double> baseline_vec;
};

