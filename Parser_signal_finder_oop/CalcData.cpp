#include "CalcData.h"

#include <iostream>
using namespace std;


CalcData::CalcData(std::vector< std::vector<double> > data)
{
	CalcBaseline calc_baseline(data[0]);
	baseline = calc_baseline.GetBaseline();
	//cout << "calc_baseline.GetBaseline() = " << calc_baseline.GetBaseline() << endl;
}


CalcData::~CalcData()
{
}
