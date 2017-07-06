#include "CalcBaselineTrivial.h"


CalcBaselineTrivial::CalcBaselineTrivial(std::vector<double> yv, const int n_points)
{
	baseline = 0;
	for (int i = 0; i < n_points; i++)
	{
		baseline += yv[i];
	}

	baseline /= n_points;
}


CalcBaselineTrivial::~CalcBaselineTrivial()
{
}
