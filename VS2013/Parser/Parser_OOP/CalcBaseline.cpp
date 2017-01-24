#include "CalcBaseline.h"



CalcBaseline::CalcBaseline(std::vector<double> yv)
{
	baseline = 0;
	const int n_points = 1000;
	for (int i = 0; i < n_points; i++)
	{
		baseline += yv[i];
	}

	baseline /= n_points;

	baseline_vec.resize( yv.size() );
	for (int i = 0; i < yv.size(); i++)
	{
		baseline_vec[i] = baseline;
	}
}


CalcBaseline::~CalcBaseline()
{
}

double CalcBaseline::GetBaseline()
{
	return baseline;
}

std::vector<double>& CalcBaseline::GetBaselineVec()
{
	return baseline_vec;
}
