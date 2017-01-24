#include "CalcData.h"

#include <iostream>
#include <algorithm>
using namespace std;


CalcData::CalcData(std::vector< std::vector<double> >& data_, std::vector<double>& time) : data(data_), time(time)
{
	const int n_ch = data.size();
	
	CalcBaseline calc_baseline_ch1(data[0]);
	CalcBaseline calc_baseline_ch3(data[1]);

	//cout <<  "calc_baseline_ch1.GetBaseline() = " << calc_baseline_ch1.GetBaseline() << endl;
	
	baseline.resize(n_ch);
	baseline[0] = calc_baseline_ch1.GetBaseline();
	baseline[1] = calc_baseline_ch3.GetBaseline();

	vector<double>::const_iterator it_b_0 = data[0].begin();
	vector<double>::const_iterator it_e_0 = data[0].end();
	vector<double>::const_iterator it_b_1 = data[1].begin();
	vector<double>::const_iterator it_e_1 = data[1].end();

	min.resize(n_ch);
	min[0] = *min_element(it_b_0, it_e_0);
	min[1] = *min_element(it_b_1, it_e_1);

	max.resize(n_ch);
	max[0] = *max_element(it_b_0, it_e_0);
	max[1] = *max_element(it_b_1, it_e_1);

	CalcDer calc_der_ch1(data[1], 41);
	der_data.resize(n_ch);
	der_data[1] = calc_der_ch1.GetDer();
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

std::vector<std::vector<double>>& CalcData::GetDer()
{
	return der_data;
}

std::vector<std::vector<double>>& CalcData::GetInt()
{
	return int_data;
}

std::vector<double>& CalcData::GetMax()
{
	return max;
}

std::vector<double>& CalcData::GetMin()
{
	return min;
}
