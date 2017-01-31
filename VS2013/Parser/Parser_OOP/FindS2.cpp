#include "FindS2.h"
#include "TH1F.h"

#include <iostream>
using namespace std;

FindS2::FindS2(std::vector<int>& peak_position, const int n_points_data, double HORIZ_INTERVAL, const double time_th_left, const double time_th_right)
{
	const double max_time = n_points_data * HORIZ_INTERVAL;
	const int n_peaks = peak_position.size();
	
	const int n_bins = 20;
	TH1F hist_1("h1", "h1 title", n_bins, 0, max_time);
	for (int i = 0; i < peak_position.size(); i++){ hist_1.Fill(peak_position[i] * HORIZ_INTERVAL); }
	const int y_max = hist_1.GetMaximumBin();
	const double x_max = hist_1.GetXaxis()->GetBinCenter(y_max);//find time of max bin

	//cout << "x_max = " << x_max << endl;
	//cout << "y_max = " << y_max << endl;

	//find the nearest peak
	int closest_peak_index = 0;
	double dist = max_time;
	for (int i = 0; i < n_peaks; i++)
	{
		double dist_tmp = fabs(peak_position[i] * HORIZ_INTERVAL - x_max);
		if (dist_tmp < dist)
		{
			dist = dist_tmp;
			closest_peak_index = i;
		}
	}


	//find right edge of s2
	double t_right = max_time;
	for (int i = closest_peak_index; i < (n_peaks - 1); i++)
	{
		t_right = peak_position[i] * HORIZ_INTERVAL + 1000;
		if (((peak_position[i + 1] - peak_position[i]) * HORIZ_INTERVAL) > time_th_right)
		{			
			break;
		}
		if ( i == (n_peaks - 2) )
		{
			t_right = peak_position[i+1] * HORIZ_INTERVAL + 1000;;
		}
	}
	if (t_right > max_time){ t_right = max_time; }


	//find left edge of s2
	double t_left = 0;
	for (int i = closest_peak_index; i > 0; i--)
	{
		t_left = peak_position[i] * HORIZ_INTERVAL - 500;
		if (((peak_position[i] - peak_position[i - 1]) * HORIZ_INTERVAL) > time_th_left)
		{
			break;
		}
		if (i == 1)
		{
			t_left = peak_position[0] * HORIZ_INTERVAL - 500;
		}
	}
	if (t_left < 0){ t_left = 0; }

	point_s2_left = t_left / HORIZ_INTERVAL;
	point_s2_right = t_right / HORIZ_INTERVAL;

	//cout << "point_s2_left = " << point_s2_left * HORIZ_INTERVAL << endl;
	//cout << "point_s2_right = " << point_s2_right * HORIZ_INTERVAL << endl;
}


FindS2::~FindS2()
{
}

int FindS2::GetPointS2Left()
{
	return point_s2_left;
}
int FindS2::GetPointS2Right()
{
	return point_s2_right;
}
