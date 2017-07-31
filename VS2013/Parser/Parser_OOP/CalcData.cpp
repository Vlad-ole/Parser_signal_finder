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
#include "CalcDoubleIntegralCalib.h"
#include "ChCharacteristics.h"
#include "RunDescription.h"

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


CalcData::CalcData(std::vector< std::vector<double> >& data_, std::vector<double>& time, double HORIZ_INTERVAL) : data(data_), time(time)
{
	const int n_ch = data.size();
	const int n_points = data[0].size();

	vector<double> der_data_tmp(n_points);
	integral_one_peak.resize(n_ch);

	min.resize(n_ch);
	max.resize(n_ch);
	der_min_position.resize(n_ch);
	der_max_position.resize(n_ch);
	for (int i = 0; i < n_ch; i++)
	{
		//cout << "ch = " << i << endl;
		
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

		vector<double> data_without_slope = TypeConvertion::GetDifference(invert_data, baseline_vec[i]);
		PeakFinderFind peak_finder_find(data_without_slope/*invert_data*/, der_data[i], 0, 1 /*this parameter is very important*/, HORIZ_INTERVAL);
		local_baseline_v.push_back(peak_finder_find.GetLocalBaselineV());
		vector< pair<int, int> > pair_vec = peak_finder_find.GetPeakPositions();
		vector<int> signals_values_x_first(pair_vec.size());
		vector<int> signals_values_x_second(pair_vec.size());
		for (int j = 0; j < pair_vec.size(); j++)
		{
			signals_values_x_first[j] = pair_vec[j].first;
			signals_values_x_second[j] = pair_vec[j].second;
		}
		signals_x_start_v.push_back(signals_values_x_first);
		signals_x_stop_v.push_back(signals_values_x_second);

		//caclulate intergal of individual peaks
		double integral_one_event_tmp = 0;
		for (int j = 0; j < pair_vec.size(); j++)
		{			
			//choose region  
			//if ( (signals_values_x_second[j] * HORIZ_INTERVAL) < 30000)			
			{
				double integral_tmp = 0;
				for (int k = signals_values_x_first[j]; k < signals_values_x_second[j]; k++)
				{
					integral_tmp += (data_without_slope[k] - local_baseline_v[i][j]) * HORIZ_INTERVAL;
				}
				integral_one_peak[i].push_back(integral_tmp);

				//if (true)//algorithm is not ideal, so I should add some cuts (depend from ch_id and experimental conditions)
				//{
				//	integral_one_event_tmp += integral_tmp;
				//}
				
			}			
		}
		//integral_one_event.push_back(integral_one_event_tmp);

		//calc num of pe for one event
		ChCharacteristics ch_characteristics;
		vector<ChCharacteristicsStruct> ch_characteristics_struct = ch_characteristics.GetChCharacteristics();
		double num_of_pe_in_event = -1;
		for (int k = 0; k < ch_characteristics_struct.size(); k++)
		{
			if (ch_characteristics_struct[k].ch_id == GetChId(i) && ch_characteristics_struct[k].is_spe_separated_from_noise && ch_characteristics_struct[k].is_physical)
			{
				num_of_pe_in_event = 0;
				for (int j = 0; j < integral_one_peak[i].size(); j++)
				{
					if (integral_one_peak[i][j] > ch_characteristics_struct[k].spe_min) //algorithm is not ideal, so I should add some cuts (depend from ch_id)
					{
						double n_pe_one_peak_tmp = integral_one_peak[i][j] / ch_characteristics_struct[k].spe_mean;
						num_of_pe_in_event += n_pe_one_peak_tmp; //should I round this value to integer?
					}
				}
				break;
			}			
		}
		num_of_pe_in_event_vec.push_back(num_of_pe_in_event);
		

		//double integral calib
		CalcDoubleIntegralCalib calc_double_intergral_calib(invert_data, pair_vec, HORIZ_INTERVAL);
		double_integral_vec.push_back(calc_double_intergral_calib.GetDoubleIntegralVec());
		double_integral_vec_y.push_back(calc_double_intergral_calib.GetDoubleIntegralVecVy());
		
		//finaly, we calculate integral of signal
		CalcIntegral calc_integral_nontriv_baseline(invert_data, baseline[i], baseline_vec[i], 35000, 160000, HORIZ_INTERVAL);
		integral.push_back(calc_integral_nontriv_baseline.GetIntegrtal());
	}
	
	//const double cut_th_low_MHz = 0;
	//const double cut_th_high_MHz = 1000;
	//FTFilter ft_filter_caen(data[1], cut_th_low_MHz, cut_th_high_MHz, HORIZ_INTERVAL);
	//yv_cut = ft_filter_caen.GetYvCut();

}


CalcData::~CalcData()
{
}

std::vector< std::vector<double> >& CalcData::GetLocalBaselineV()
{
	return local_baseline_v;
}

std::vector< std::vector<int> >& CalcData::GetSignalsXStart()
{
	return signals_x_start_v;
}

std::vector< std::vector<int> >& CalcData::GetSignalsXStop()
{
	return signals_x_stop_v;
}

std::vector<double>& CalcData::GetNumOfPeInEventVec()
{
	return num_of_pe_in_event_vec;
}

//CalcData& CalcData::operator=(const CalcData& CD)
//{
//
//}

std::vector< std::vector<double> >& CalcData::GetIntegralOnePeak()
{
	return integral_one_peak;
}

std::vector<double>& CalcData::GetIntegralOneEvent()
{
	return integral_one_event;
}

std::vector<double> CalcData::GetInvertSignal(std::vector<double> yv, double baseline)
{
	vector<double> yv_double_invert(yv.size());
	for (int i = 0; i < yv.size(); i++)
	{
		yv_double_invert[i] = -yv[i] + 2 * baseline;
	}
	return yv_double_invert;
}

std::vector< std::vector<double> >& CalcData::GetDoubleIntegralVec()
{
	return double_integral_vec;
}

std::vector< std::vector<double> >& CalcData::GetDoubleIntegralVecY()
{
	return double_integral_vec_y;
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