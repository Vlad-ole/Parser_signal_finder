#include "CalcBaselineMedianFilter.h"
#include <iostream>

using namespace std;

CalcBaselineMedianFilter::CalcBaselineMedianFilter(std::vector<double> yv, const int time_left, const int time_right, const int param_n_points ,double HORIZ_INTERVAL)
{
	const int yv_size = yv.size();
	baseline_vec.resize(yv_size);

	const int point_left = time_left / HORIZ_INTERVAL;
	const int point_right = time_right / HORIZ_INTERVAL;

	// http://www.librow.com/articles/article-1
	//   1D MEDIAN FILTER implementation
	//     signal - input signal
	//     result - output signal
	//     N      - length of the signal
	
	//   Move window through all elements of the signal
	const int half_step = param_n_points / 2;
	for (int i = point_left + half_step; i < point_right - half_step; i++)
	{
		vector<double> window(param_n_points);
		for (int j = 0; j < param_n_points; j++)
		{
			window[j] = yv[i - half_step + j];

			//   Order elements (only half of them)
			for (int j = 0; j < half_step + 1; ++j)
			{
				//   Find position of minimum element
				int min = j;
				for (int k = j + 1; k < param_n_points; ++k)
					if (window[k] < window[min])
						min = k;
				//   Put found minimum element in its place
				const double temp = window[j];
				window[j] = window[min];
				window[min] = temp;
			}
			//   Get result - the middle element
			baseline_vec[i - half_step] = window[half_step];
		}
	}
	
	
	//void _medianfilter(const element* signal, element* result, int N)
	//{
	//	//   Move window through all elements of the signal
	//for (int i = 2; i < N - 2; ++i)
	//{
	//	//   Pick up window elements
	//	element window[5];
	//	for (int j = 0; j < 5; ++j)
	//		window[j] = signal[i - 2 + j];
	//	//   Order elements (only half of them)
	//	for (int j = 0; j < 3; ++j)
	//	{
	//		//   Find position of minimum element
	//		int min = j;
	//		for (int k = j + 1; k < 5; ++k)
	//			if (window[k] < window[min])
	//				min = k;
	//		//   Put found minimum element in its place
	//		const element temp = window[j];
	//		window[j] = window[min];
	//		window[min] = temp;
	//	}
	//	//   Get result - the middle element
	//	result[i - 2] = window[2];
	//}
	//}


}


CalcBaselineMedianFilter::~CalcBaselineMedianFilter()
{
}
