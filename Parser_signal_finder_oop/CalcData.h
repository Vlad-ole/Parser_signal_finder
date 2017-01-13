#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "CalcBaseline.h"

class CalcData
{
public:
	CalcData(std::vector< std::vector<double> > data);
	~CalcData();

	double baseline;
private:
};

