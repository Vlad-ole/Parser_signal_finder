#pragma once

#include <iostream>
#include <vector>

class CalcBaseline
{
public:
	CalcBaseline(std::vector<double> yv);
	~CalcBaseline();

	double GetBaseline();
private:
	double baseline;
};

