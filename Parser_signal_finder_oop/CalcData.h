#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "CalcBaseline.h"

class CalcData
{
public:
	CalcData(std::vector< std::vector<double> > data, std::vector<double> time);
	~CalcData();

	std::vector< std::vector<double> >& GetData();
	std::vector<double>& GetTime();
	std::vector<double>& GetBaseline();
private:
	std::vector< std::vector<double> > data;
	std::vector<double> time;
	std::vector<double> baseline;
};

