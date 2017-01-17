#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "CalcBaseline.h"

class CalcData
{
public:
	CalcData(std::vector< std::vector<double> >& data, std::vector<double>& time);
	~CalcData();

	std::vector< std::vector<double> >& GetData();
	std::vector<double>& GetTime();

	std::vector<double>& GetBaseline();
	std::vector< std::vector<double> >& GetDer();
	std::vector<double>& GetMax();
	std::vector<double>& GetMin();
private:
	std::vector< std::vector<double> >& data;
	std::vector<double>& time;

	std::vector<double> max;
	std::vector<double> min;
	
	std::vector<double> baseline;
	std::vector< std::vector<double> > der;
	
};

