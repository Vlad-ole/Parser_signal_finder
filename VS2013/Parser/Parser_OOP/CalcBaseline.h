#pragma once

#include <iostream>
#include <vector>

#include "TSpectrum.h"

class CalcBaseline
{
public:
	CalcBaseline(std::vector<double> yv, const int point_s2_left, const int point_s2_right);
	~CalcBaseline();

	double GetBaseline();
	std::vector<double>& GetBaselineVec();
private:
	double baseline;
	std::vector<double> baseline_vec;
	TSpectrum *s;
};

