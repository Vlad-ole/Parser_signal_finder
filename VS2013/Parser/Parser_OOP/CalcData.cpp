#include "CalcData.h"
#include "CalcIntegral.h"
#include "FindS2.h"
#include "CalcIntegralS1.h"
#include "FTFilter.h"

#include "CalcBaselineTrivial.h"
#include "CalcBaselineZeroComp.h"
#include "CalcBaselineMedianFilter.h"

#include "CalcDoubleIntegral.h"

#include "PeakFinderFind.h"

#include "TypeConvertion.h"

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


CalcData::CalcData(std::vector< std::vector<double> >& data_, std::vector<double>& time, double HORIZ_INTERVAL) : data(data_), time(time)
{
	const int n_ch = data.size();
	const int n_points = data[0].size();

	vector<double> der_data_tmp(n_points);

	min.resize(n_ch);
	max.resize(n_ch);
	der_min_position.resize(n_ch);
	der_max_position.resize(n_ch);
	for (int i = 0; i < n_ch; i++)
	{
		//it's nesessry to find trivial baseline. We can use this value for more complex algorithms
		CalcBaselineTrivial calc_baseline(data[i], 30000, HORIZ_INTERVAL);
		baseline.push_back(calc_baseline.GetBaseline());

		//it's comfortable to work with invert signal
		vector<double> invert_data = GetInvertSignal(data[i], baseline[i]);

		CalcDoubleIntegral calc_double_int(invert_data, baseline[i], HORIZ_INTERVAL);
		int_data.push_back(calc_double_int.GetDataIntegrtal());

		//min and max values will help to avoid signals with saturation
		vector<double>::const_iterator it_b = invert_data.begin();
		vector<double>::const_iterator it_e = invert_data.end();
		min[i] = *min_element(it_b, it_e);
		max[i] = *max_element(it_b, it_e);

		//to find extremum in der and change baseline (optional)
		CalcDer calc_der_tmp(invert_data, 101, 1);
		der_data_tmp = calc_der_tmp.GetDer();
		der_min_position[i] = distance(der_data_tmp.begin(), min_element(der_data_tmp.begin(), der_data_tmp.end()));
		der_max_position[i] = distance(der_data_tmp.begin(), max_element(der_data_tmp.begin(), der_data_tmp.end()));

		//to find nonoverlapped signals
		CalcDer calc_der(invert_data, 21, 1);
		der_data.push_back(calc_der.GetDer());

		CalcDer calc_smooth(invert_data, 21, 0);
		smooth_data.push_back(calc_smooth.GetDer());		

		//CalcBaselineMedianFilter calc_baseline_median_filter(invert_data, 0, 160000, 11, HORIZ_INTERVAL);
		//baseline_vec.push_back(calc_baseline_median_filter.GetBaselineVec());

		CalcBaselineZeroComp calc_baseline_zero_comp(invert_data/*smooth_data[i]*/, 40000, 100000, calc_baseline.GetBaseline(), der_max_position[i], HORIZ_INTERVAL);
		baseline_vec.push_back(calc_baseline_zero_comp.GetBaselineVec());

		//CalcIntegral calc_integral(data[i], baseline[i], 37800, 68300, HORIZ_INTERVAL);
		//integral.push_back(calc_integral.GetIntegrtal());

		PeakFinderFind peak_finder_find(TypeConvertion::GetDifference(invert_data, baseline_vec[i]) /*invert_data*/, der_data[i], 0, 1, HORIZ_INTERVAL);
		//signals_pair_values.push_back(peak_finder_find.GetPeakPositions());
		vector< pair<int, int> > pair_vec = peak_finder_find.GetPeakPositions();
		vector<int> signals_values_x_first(pair_vec.size());
		vector<int> signals_values_x_second(pair_vec.size());
		for (int j = 0; j < pair_vec.size(); j++)
		{
			signals_values_x_first[j] = pair_vec[j].first;
			signals_values_x_second[j] = pair_vec[j].second;
			//cout << pair_vec[j].first << "\t" << pair_vec[j].second << endl;
			//cout << signals_values_x_first[j] << "\t" << signals_values_x_second[j] << endl;
		}
		signals_x_start_v.push_back(signals_values_x_first);
		signals_x_stop_v.push_back(signals_values_x_second);
		//cout << signals_values_x_first[0] << endl;
		//vector<vector<int>> tmp_v;
		//tmp_v.push_back(signals_values_x_first);
		//tmp_v.push_back(signals_values_x_second);
		//signals_position_values.push_back(tmp_v);

		//cout << signals_position_values[i][0][0] << endl;

		//vector<double> signals_values_x;
		//vector<double> signals_values_y;
		//vector< pair<int, int> > pair_vec = peak_finder_find.GetPeakPositions();
		//for (int j = 0; j < pair_vec.size(); j++)
		//{
		//	for (int k = pair_vec[j].first; k < pair_vec[j].second; k++)
		//	{
		//		signals_values_x.push_back(k * HORIZ_INTERVAL);
		//		signals_values_y.push_back(invert_data[k]);
		//	}
		//}

		//finaly, we calculate integral of signal
		CalcIntegral calc_integral_nontriv_baseline(invert_data, baseline[i], baseline_vec[i], 35000, 160000, HORIZ_INTERVAL);
		integral.push_back(calc_integral_nontriv_baseline.GetIntegrtal());
	}
	
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

//std::pair<std::vector<double>, std::vector<double> >  CalcData::GetSignalsValues()
//{
//	return signals_values_pair;
//}

//std::vector< std::vector< pair<int, int> > > CalcData::GetSignalsPairValues()
//{
//	return signals_pair_values;
//}

//std::vector< std::vector< std::vector<int> > > CalcData::GetSignalsPositionValues()
//{
//	return signals_position_values;
//}

std::vector< std::vector<int> >& CalcData::GetSignalsXStart()
{
	return signals_x_start_v;
}

std::vector< std::vector<int> >& CalcData::GetSignalsXStop()
{
	return signals_x_stop_v;
}

//CalcData& CalcData::operator=(const CalcData& CD)
//{
//
//}

std::vector<double> CalcData::GetInvertSignal(std::vector<double> yv, double baseline)
{
	vector<double> yv_double_invert(yv.size());
	for (int i = 0; i < yv.size(); i++)
	{
		yv_double_invert[i] = -yv[i] + 2 * baseline;
	}
	return yv_double_invert;
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

std::vector<int>& CalcData::GetDerMaxPosition()
{
	return der_max_position;
}

std::vector<int>& CalcData::GetDerMinPosition()
{
	return der_min_position;
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


vector<double> CalcData::GetIntegral()
{
	return integral;
}

vector<double> CalcData::GetIntegralS2()
{
	return integral_s2;
}

double CalcData::GetIntegral_s1_caen_outside_the_trigger()
{
	return integral_s1_caen_outside_the_trigger;
}