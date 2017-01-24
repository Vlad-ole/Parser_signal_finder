#include "CalcData.h"
#include "CalcIntegral.h"

#include <iostream>
#include <algorithm>
using namespace std;


CalcData::CalcData(std::vector< std::vector<double> >& data_, std::vector<double>& time) : data(data_), time(time)
{
	const int n_ch = data.size();
	
	CalcBaseline calc_baseline_ortec(data[0]);
	CalcBaseline calc_baseline_caen(data[1]);

	//cout <<  "calc_baseline_ch1.GetBaseline() = " << calc_baseline_ch1.GetBaseline() << endl;
	
	baseline.resize(n_ch);
	baseline[0] = calc_baseline_ortec.GetBaseline();
	baseline[1] = calc_baseline_caen.GetBaseline();

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

	
	CalcDer calc_der_ortec(data[0], 41);
	CalcDer calc_der_caen(data[1], 41);
	
	der_data.resize(n_ch);
	der_data[0] = calc_der_ortec.GetDer();
	der_data[1] = calc_der_caen.GetDer();

	PeakFinder pk_fndr(calc_der_caen.GetDer(), time, 5);
	peak_position.resize(n_ch);
	peak_position[1] = pk_fndr.GetPeakPosition();

	
	CalcIntegral calc_integral_ortec(data[0], calc_baseline_caen.GetBaselineVec(), 0, 0, 5);
	CalcIntegral calc_integral_caen(data[1], calc_baseline_caen.GetBaselineVec(), 0, 0, 5);
	int_data.resize(n_ch);
	int_data[0] = calc_integral_ortec.GetDataIntegrtal();
	int_data[1] = calc_integral_caen.GetDataIntegrtal();
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

std::vector< std::vector<double> >& CalcData::GetPeakPosition()
{
	return peak_position;
}
