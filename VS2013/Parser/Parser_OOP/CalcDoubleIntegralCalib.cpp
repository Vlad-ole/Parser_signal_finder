#include "CalcDoubleIntegralCalib.h"
#include "CalcDoubleIntegralCalib.h"

using namespace std;

CalcDoubleIntegralCalib::CalcDoubleIntegralCalib(std::vector<double> data, std::vector< std::pair<int, int> >& pair_vec, double HORIZ_INTERVAL)
{
	const int veto_window_p = 10000 / HORIZ_INTERVAL;
	const int local_baseline_window_p = 300 / HORIZ_INTERVAL; 
	//const int local_baseline_window_shift_p = 0 / HORIZ_INTERVAL;

	vector<int> signals_values_x_first(pair_vec.size());
	vector<int> signals_values_x_second(pair_vec.size());
	for (int j = 0; j < pair_vec.size(); j++)
	{
		signals_values_x_first[j] = pair_vec[j].first;
		signals_values_x_second[j] = pair_vec[j].second;
	}
	
	for (int j = 0; j < pair_vec.size(); j++)
	{

		if (pair_vec.size() == 1)
		{
			//have not realised yet
		}
		else
		{
			if (j < (pair_vec.size() - 1))
			{
				if (signals_values_x_first[j + 1] - signals_values_x_second[j] > veto_window_p)
				{
					vector<double> data_integrtal;

					//calc local baseline
					double local_baseline = 0;
					const int k_to = (signals_values_x_first[j] - local_baseline_window_p) > 0 ? (signals_values_x_first[j] - local_baseline_window_p) : 0;
					for (int k = (signals_values_x_first[j]); k > k_to; k++)
					{
						local_baseline += data[k];
					}
					local_baseline /= (signals_values_x_first[j] - k_to);


					//calc integral func
					double summ = 0;
					for (int k = signals_values_x_first[j]; k < signals_values_x_first[j] + veto_window_p; k++)
					{
						summ += (data[k] - local_baseline);
						data_integrtal.push_back(summ * HORIZ_INTERVAL);
					}

					//calc double integral
					double double_integral = 0;
					for (int k = 0; k < veto_window_p; k++)
					{
						double_integral += data_integrtal[k];
					}

					double_integral_vec.push_back(double_integral);

				}
			}
		}

	}
}


CalcDoubleIntegralCalib::~CalcDoubleIntegralCalib()
{
}
