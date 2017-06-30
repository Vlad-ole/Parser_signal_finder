#include "CalcData.h"
#include "CalcIntegral.h"
#include "FindS2.h"
#include "CalcIntegralS1.h"
#include "FTFilter.h"

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


CalcData::CalcData(std::vector< std::vector<double> >& data_, std::vector<double>& time) : data(data_), time(time)
{
	const int n_ch = data.size();
	const int n_points = data[0].size();
	double HORIZ_INTERVAL = 16;
	
	//cout <<  "calc_baseline_ch1.GetBaseline() = " << calc_baseline_ch1.GetBaseline() << endl;
	

	
	vector<double>::const_iterator it_b_0 = data[0].begin();
	vector<double>::const_iterator it_e_0 = data[0].end();
	//vector<double>::const_iterator it_b_1 = data[1].begin();
	//vector<double>::const_iterator it_e_1 = data[1].end();

	min.resize(n_ch);
	min[0] = *min_element(it_b_0, it_e_0);
	//min[1] = *min_element(it_b_1, it_e_1);

	max.resize(n_ch);
	max[0] = *max_element(it_b_0, it_e_0);
	//max[1] = *max_element(it_b_1, it_e_1);

	
	//run_6
	//const double n_points_param = 101; //odd number!
	//const double der_th = 3.5;
	//const double max_dist_left = 2000;//ns
	//const double max_dist_right = 5000;//ns
	//const double trigg_time = 0;//ns

	////run_7
	//const double n_points_param = 41; //odd number!
	//const double der_th = 5;
	//const double max_dist_left = 2000;//ns
	//const double max_dist_right = 5000;//ns
	//const double time_s1_left = 4500;//ns
	//const double time_s1_right = 6000;//ns
	////const double time_s1_left = 6000;//ns
	////const double time_s1_right = 8000;//ns

	////CalcDer calc_der_ortec(data[0], n_points_param);
	//CalcDer calc_der_caen(data[1], n_points_param);
	
	//der_data.resize(n_ch);
	//der_data[0].resize(n_points);
	////der_data[0] = calc_der_ortec.GetDer();
	//der_data[1] = calc_der_caen.GetDer();

	//smooth_data.resize(n_ch);
	//smooth_data[0].resize(der_data[0].size());//dummy
	//smooth_data[1].resize(der_data[0].size());//dummy
	//smooth_data[1] = calc_der_caen.GetSmooth();
	

	//PeakFinder pk_fndr_caen(calc_der_caen.GetDer(), time, der_th);
	//peak_position.resize(n_ch);
	////peak_position[0].resize(n_points);
	//peak_position[1] = pk_fndr_caen.GetPeakPosition();

	//FindS2 fnd_s2_caen(pk_fndr_caen.GetPeakPosition(), n_points, HORIZ_INTERVAL, max_dist_left, max_dist_right);
	//point_s2_left = fnd_s2_caen.GetPointS2Left();
	//point_s2_right = fnd_s2_caen.GetPointS2Right();


	////CalcBaseline calc_baseline_ortec(data[0], peak_position[0][point_s2_left], peak_position[0][point_s2_right]);
	//CalcBaseline calc_baseline_caen(data[1], point_s2_left, point_s2_right);
	//baseline.resize(n_ch);
	////baseline[0] = calc_baseline_ortec.GetBaseline();
	//baseline[1] = calc_baseline_caen.GetBaseline();
	//baseline_vec.resize(n_ch);
	//baseline_vec[1] = calc_baseline_caen.GetBaselineVec();

	//vector<double> tmp(der_data[1].size());
	//CalcIntegral calc_integral_ortec(data[0], calc_baseline_caen.GetBaselineVec(), 0, 0, 5);
	////CalcIntegral calc_integral_caen(data[1], calc_baseline_caen.GetBaselineVec(), 0, 0, 5);
	//CalcIntegral calc_integral_caen_s2(data[1], calc_baseline_caen.GetBaselineVec(), point_s2_left * HORIZ_INTERVAL, point_s2_right * HORIZ_INTERVAL, HORIZ_INTERVAL);
	//CalcIntegralS1 calc_integral_caen_s1(data[1], time_s1_left, time_s1_right, point_s2_left, HORIZ_INTERVAL, peak_position[1]);

	//CalcIntegralS1 calc_integral_caen_s1_left(data[1], 0, 4500, point_s2_left, HORIZ_INTERVAL, peak_position[1]);
	//CalcIntegralS1 calc_integral_caen_s1_right(data[1], 6000, point_s2_left * HORIZ_INTERVAL, point_s2_left, HORIZ_INTERVAL, peak_position[1]);
	//integral_s1_caen_outside_the_trigger = calc_integral_caen_s1_left.GetIntegrtal() + calc_integral_caen_s1_right.GetIntegrtal();

	//int_data.resize(n_ch);
	//int_data[0] = calc_integral_ortec.GetDataIntegrtal();
	//int_data[1] = calc_integral_caen_s2.GetDataIntegrtal();

	//integral_s1.resize(n_ch);
	//integral_s2.resize(n_ch);
	//integral_s1[0] = 0;
	//integral_s2[0] = 0;
	//integral_s1[1] = calc_integral_caen_s1.GetIntegrtal();
	////integral_s1[1] = calc_integral_caen_s1_left.GetIntegrtal() + calc_integral_caen_s1_right.GetIntegrtal();
	//integral_s2[1] = calc_integral_caen_s2.GetIntegrtal();

	//const double cut_th_low_MHz = 0;
	//const double cut_th_high_MHz = 1000;
	//FTFilter ft_filter_caen(data[1], cut_th_low_MHz, cut_th_high_MHz, HORIZ_INTERVAL);
	//yv_cut = ft_filter_caen.GetYvCut();

}


CalcData::~CalcData()
{
}

std::vector<double>& CalcData::GetYvCut()
{
	return yv_cut;
}

std::vector< std::vector<double> >& CalcData::GetSmooth()
{
	return smooth_data;
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

std::vector<std::vector<double>>& CalcData::GetBaselineVec()
{
	return baseline_vec;
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

std::vector< std::vector<int> >& CalcData::GetPeakPosition()
{
	return peak_position;
}

int CalcData::GetPointS2Left()
{
	return point_s2_left;
}

int CalcData::GetPointS2Right()
{
	return point_s2_right;
}


vector<double> CalcData::GetIntegralS1()
{
	return integral_s1;
}

vector<double> CalcData::GetIntegralS2()
{
	return integral_s2;
}

double CalcData::GetIntegral_s1_caen_outside_the_trigger()
{
	return integral_s1_caen_outside_the_trigger;
}