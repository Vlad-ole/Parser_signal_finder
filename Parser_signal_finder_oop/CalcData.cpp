#include "CalcData.h"

#include <iostream>
using namespace std;


CalcData::CalcData(std::vector< std::vector<double> > data, std::vector<double> time) : data(data), time(time)
{
	CalcBaseline calc_baseline_ch1(data[0]);
	CalcBaseline calc_baseline_ch3(data[1]);

	//cout <<  "calc_baseline_ch1.GetBaseline() = " << calc_baseline_ch1.GetBaseline() << endl;
	
	baseline.resize( data.size() );
	baseline[0] = calc_baseline_ch1.GetBaseline();
	baseline[1] = calc_baseline_ch3.GetBaseline();

}


CalcData::~CalcData()
{
}

std::vector<std::vector<double>>& CalcData::GetData()
{
	return data;
}

std::vector<double>& CalcData::GetTime()
{
	return time;
}

std::vector<double>& CalcData::GetBaseline()
{
	return baseline;
}
