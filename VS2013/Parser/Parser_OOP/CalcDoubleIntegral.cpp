#include "CalcDoubleIntegral.h"


CalcDoubleIntegral::CalcDoubleIntegral(std::vector<double> data, std::vector<double> baseline, const double time_scale)
{
	data_integrtal.resize(data.size());
	double summ = 0;

	for (int i = 0; i < data.size(); i++)
	{
		summ += (data[i] - baseline[i]);
		data_integrtal[i] = summ * time_scale;
	}
}


CalcDoubleIntegral::CalcDoubleIntegral(std::vector<double> data, double baseline, const double time_scale)
{
	data_integrtal.resize(data.size());
	double summ = 0;

	for (int i = 0; i < data.size(); i++)
	{
		summ += (data[i] - baseline);
		data_integrtal[i] = summ * time_scale;
	}
}


CalcDoubleIntegral::CalcDoubleIntegral(std::vector<double> data, double baseline, const int point_from, const double time_scale)
{
	data_integrtal.resize(data.size());
	double summ = 0;

	for (int i = point_from; i < data.size(); i++)
	{
		summ += (data[i] - baseline);
		data_integrtal[i] = summ * time_scale;
	}
}


CalcDoubleIntegral::~CalcDoubleIntegral()
{
}

std::vector<double> CalcDoubleIntegral::GetDataIntegrtal()
{
	return data_integrtal;
}
