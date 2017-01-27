#include "CalcIntegralS1.h"


CalcIntegralS1::CalcIntegralS1(std::vector<double>& data, double time_trigg_s1, int point_s2_left,
	double HORIZ_INTERVAL, std::vector<int>& peak_position)
{
	//find the first peak after trigger
	int peak_index_s1_first = 0;
	for (int i = 0; i < peak_position.size(); i++)
	{
		if (peak_position[i] * HORIZ_INTERVAL > time_trigg_s1)
		{
			peak_index_s1_first = i;
			break;
		}
	}

	//find the last peak before s2
	int peak_index_s1_last = 0;
	for (int i = 0; i < peak_position.size(); i++)
	{
		if (peak_position[i] > point_s2_left)
		{
			peak_index_s1_last = i - 1;
			break;
		}
	}


	//iterrate all s1 peaks 
	integral_s1_all_peaks = 0;
	for (int i = peak_index_s1_first; i <= peak_index_s1_last; i++)
	{
		const int index_start = peak_position[i] - (int)(30.0 / HORIZ_INTERVAL);
		const int index_stop = peak_position[i] + (int)(300.0 / HORIZ_INTERVAL);

		//find baseline
		int index_stop_baseline = peak_position[i] - (int)(10.0 / HORIZ_INTERVAL);
		double baseline = 0;
		for (int k = index_start; k < index_stop_baseline; k++)
		{
			baseline += data[k];
		}
		baseline /= (index_stop_baseline - index_start);

		double integral_one_peak = 0;
		for (int k = index_start; k < index_stop; k++)
		{
			integral_one_peak += data[k] - baseline;
		}
		integral_one_peak *= HORIZ_INTERVAL;

		integral_s1_all_peaks += integral_one_peak;
	}

}


CalcIntegralS1::~CalcIntegralS1()
{
}

double CalcIntegralS1::GetIntegrtal()
{
	return integral_s1_all_peaks;
}
