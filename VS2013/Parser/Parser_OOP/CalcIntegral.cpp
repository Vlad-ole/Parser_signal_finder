#include "CalcIntegral.h"

#include <iostream>
using namespace std;

CalcIntegral::CalcIntegral(std::vector<double> data, std::vector<double> baseline,
	const double time_from, const double time_to, const double time_scale)
{
	data_integrtal.resize(data.size());
	double summ = 0;

	for (int i = 0; i < data.size(); i++)
	{
		summ += (data[i] - baseline[i]);
		data_integrtal[i] = summ * time_scale;
	}

	const int point_from = time_from / time_scale;
	const int point_to = time_to / time_scale;

	integral = 0;
	for (int i = point_from; i < point_to; i++)
	{
		integral += (data[i] - baseline[i]);
	}
	integral *= time_scale;
}


CalcIntegral::~CalcIntegral()
{
}

std::vector<double> CalcIntegral::GetDataIntegrtal()
{
	return data_integrtal;
}

double CalcIntegral::GetIntegrtal()
{
	return integral;
}
