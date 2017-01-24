#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "CalcBaseline.h"
#include "CalcDer.h"
#include "PeakFinder.h"

class CalcData
{
public:
	CalcData(std::vector< std::vector<double> >& data, std::vector<double>& time);
	~CalcData();

	std::vector< std::vector<double> >& GetData();
	std::vector<double>& GetTime();

	std::vector<double>& GetBaseline();
	std::vector< std::vector<double> >& GetDer();
	std::vector< std::vector<double> >& GetInt();
	std::vector<double>& GetMax();
	std::vector<double>& GetMin();

	std::vector< std::vector<double> >& GetPeakPosition();

private:
	std::vector< std::vector<double> >& data;
	std::vector<double>& time;

	std::vector<double> max;
	std::vector<double> min;
	
	std::vector<double> baseline;
	std::vector< std::vector<double> > der_data;
	std::vector< std::vector<double> > int_data;

	std::vector<double> integral;
	std::vector< std::vector<double> > peak_position;
};

