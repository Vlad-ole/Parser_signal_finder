#include "CalcData.h"

#include <iostream>
using namespace std;


CalcData::CalcData(std::vector< std::vector<double> > data, std::vector<double> time) : fill_canv(data, time)
{
	CalcBaseline calc_baseline(data[0]);
	baseline = calc_baseline.GetBaseline();

	canv = &fill_canv.GetCanv();
}


CalcData::~CalcData()
{
}
