#include "PeakFinderFind.h"


PeakFinderFind::PeakFinderFind(std::vector<double>& yv, std::vector<double>& yv_der, const double th, const double th_der)
{
	bool is_search = true;
	int position_tmp;

	for (int i = 0; i < yv.size(); i++)
	{
		//if ((yv_der[i] < th) && is_search)
		//{
		//	is_search = false;
		//	position_tmp = i;

		//	for (int j = i; j < length; j++)
		//	{

		//	}
		//}

		//if (!is_search)
		//{
		//	if (yv[i] > pair_value.second)
		//	{
		//		pair_value.first = i;
		//		pair_value.second = yv[i];
		//	}
		//}

		//if ((yv[i] < th) && !is_search)
		//{
		//	is_search = true;
		//	peak_position.push_back(pair_value.first);
		//}
	}
}


PeakFinderFind::~PeakFinderFind()
{
}
