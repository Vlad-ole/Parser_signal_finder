#pragma once
#include "CalcBaseline.h"
class CalcBaselineMedianFilter :
	public CalcBaseline
{
public:
	CalcBaselineMedianFilter(std::vector<double> yv, const int time_left, const int time_right, const int param_n_points, double HORIZ_INTERVAL);
	~CalcBaselineMedianFilter();
};

