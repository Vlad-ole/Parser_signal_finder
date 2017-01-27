#pragma once

#include <iostream>
#include <vector>

class TypeConvertion
{
public:
	TypeConvertion();
	~TypeConvertion();
	static std::vector<float> GetVectorFloat(std::vector<double> & yv_double);
	static std::vector<double> GetVectorDouble(std::vector<float> & yv_float);
private:

};

