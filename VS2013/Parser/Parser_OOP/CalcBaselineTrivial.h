#pragma once
#include "CalcBaseline.h"
class CalcBaselineTrivial :
	public CalcBaseline
{
public:
	CalcBaselineTrivial(std::vector<double> yv, const int n_points);
	virtual ~CalcBaselineTrivial();
};

