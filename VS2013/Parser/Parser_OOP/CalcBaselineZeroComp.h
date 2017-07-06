#pragma once
#include "CalcBaseline.h"
#include "TSpectrum.h"

class CalcBaselineZeroComp :
	public CalcBaseline
{
public:
	CalcBaselineZeroComp(std::vector<double> yv, const int point_s2_left, const int point_s2_right);
	virtual ~CalcBaselineZeroComp();
protected:
	TSpectrum *s;
};

