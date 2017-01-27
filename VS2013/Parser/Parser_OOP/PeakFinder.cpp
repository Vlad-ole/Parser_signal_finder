#include "PeakFinder.h"

using namespace std;

PeakFinder::PeakFinder(std::vector<double>& yv, std::vector<double>& time, const double th)
{
	bool is_search = true;
	pair<double, double> pair_value;
	

	for (int i = 0; i < yv.size(); i++)
	{
		if ((yv[i] > th) && is_search)
		{
			is_search = false;
			pair_value.second = -1E10;
		}

		if (!is_search)
		{
			if (yv[i] > pair_value.second)
			{
				pair_value.first = i;
				pair_value.second = yv[i];
			}
		}

		if ((yv[i] < th) && !is_search)
		{
			is_search = true;
			peak_position.push_back(pair_value.first);
		}
	}


}


PeakFinder::~PeakFinder()
{
}

std::vector<int>& PeakFinder::GetPeakPosition()
{
	return peak_position;
}