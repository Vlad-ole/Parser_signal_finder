#include "CalcDoubleIntegralCalib.h"

using namespace std;

CalcDoubleIntegralCalib::CalcDoubleIntegralCalib(std::vector<double> data, std::vector< std::pair<int, int> >& pair_vec, double HORIZ_INTERVAL)
{
	const int veto_window_p = 20000 / HORIZ_INTERVAL;
	const int integral_window = 15000 / HORIZ_INTERVAL;
	const int local_baseline_window_p = 10000 / HORIZ_INTERVAL; 
	//const int local_baseline_window_shift_p = 0 / HORIZ_INTERVAL;

	double_integral_vec_vy.resize(data.size());

	vector<int> signals_values_x_first(pair_vec.size());
	vector<int> signals_values_x_second(pair_vec.size());
	for (int j = 0; j < pair_vec.size(); j++)
	{
		signals_values_x_first[j] = pair_vec[j].first;
		signals_values_x_second[j] = pair_vec[j].second;
	}
	
	for (int j = 0; j < pair_vec.size(); j++)
	{
		bool is_allow_calc = false;
		bool is_left_cond = (signals_values_x_first[j] - veto_window_p) > 0;
		bool is_right_cond = (signals_values_x_second[j] + veto_window_p) < 9999;
		bool is_electronical_noise = (signals_values_x_first[j] > (30000 / HORIZ_INTERVAL)) &&
			(signals_values_x_second[j] < (35000 / HORIZ_INTERVAL));

		if (is_left_cond && is_right_cond && !is_electronical_noise)
		{
			if (pair_vec.size() == 1)
			{
				is_allow_calc = true;
			}
			else
			{
				
				if (j == 0) //check only right condition for the first peak
				{
					is_allow_calc = (signals_values_x_first[j + 1] - signals_values_x_second[j]) > veto_window_p;
				}
				else if (j == (pair_vec.size() - 1)) //check only left condition for the last peak
				{
					is_allow_calc = (signals_values_x_first[j] - signals_values_x_second[j - 1]) > veto_window_p;
				}
				else // check left & right conditions in another case
				{
					is_allow_calc = ((signals_values_x_first[j] - signals_values_x_second[j - 1]) > veto_window_p) && 
						((signals_values_x_first[j + 1] - signals_values_x_second[j]) > veto_window_p);
				}
			}
		}

		if (is_allow_calc)
		{
			vector<double> data_integrtal;

			//calc local baseline
			double local_baseline = 0;
			const int k_to = (signals_values_x_first[j] - local_baseline_window_p) > 0 ? (signals_values_x_first[j] - local_baseline_window_p) : 0;
			for (int k = (signals_values_x_first[j]); k > k_to; k--)
			{
				local_baseline += data[k];
			}
			local_baseline /= (signals_values_x_first[j] - k_to);
			

			//calc integral func
			double summ = 0;
			for (int k = signals_values_x_first[j]; k < signals_values_x_first[j] + integral_window; k++)
			{
				summ += (data[k] - local_baseline);
				data_integrtal.push_back(summ * HORIZ_INTERVAL);
				double_integral_vec_vy[k] = summ * HORIZ_INTERVAL;
			}

			//calc double integral
			double double_integral = 0;
			for (int k = 0; k < integral_window; k++)
			{
				double_integral += data_integrtal[k];
			}


			double_integral_vec.push_back(double_integral);

		}

	}
}


CalcDoubleIntegralCalib::~CalcDoubleIntegralCalib()
{
}

std::vector<double> CalcDoubleIntegralCalib::GetDoubleIntegralVec()
{
	return double_integral_vec;
}

std::vector<double> CalcDoubleIntegralCalib::GetDoubleIntegralVecVy()
{
	return double_integral_vec_vy;
}
