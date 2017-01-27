#include "TypeConvertion.h"


TypeConvertion::TypeConvertion()
{
}


TypeConvertion::~TypeConvertion()
{
}

std::vector<float> TypeConvertion::GetVectorFloat(std::vector<double>& yv_double)
{
	std::vector<float> yv_float(yv_double.size());
	for (int i = 0; i < yv_double.size(); i++)
	{
		yv_float[i] = yv_double[i];
	}

	return yv_float;
}

std::vector<double> TypeConvertion::GetVectorDouble(std::vector<float>& yv_float)
{
	std::vector<double> yv_double(yv_float.size());
	for (int i = 0; i < yv_float.size(); i++)
	{
		yv_double[i] = yv_float[i];
	}

	return yv_double;
}