#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "CalcBaseline.h"
#include "FillCanv.h"

class CalcData
{
public:
	CalcData(std::vector< std::vector<double> > data, std::vector<double> time);
	~CalcData();

	double baseline;
	TCanvas *canv;
private:
	FillCanv fill_canv;
};

