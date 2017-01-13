#include "CalcBaseline.h"



CalcBaseline::CalcBaseline(std::vector<double> yv)
{
	baseline = 0;
	for (int i = 0; i < 100; i++)
	{
		baseline += yv[i];
	}

	baseline /= 100;
}


CalcBaseline::~CalcBaseline()
{
}

double CalcBaseline::GetBaseline()
{
	return baseline;
}
