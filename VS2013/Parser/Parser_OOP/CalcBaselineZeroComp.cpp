#include "CalcBaselineZeroComp.h"
#include "TypeConvertion.h"

#include <iostream>
using namespace std;

CalcBaselineZeroComp::CalcBaselineZeroComp(std::vector<double> yv, const int time_left, const int time_right, const double baseline, const int der_max_position, double HORIZ_INTERVAL)
{
	const int yv_size = yv.size();
	baseline_vec.resize(yv_size);

	const int point_left = time_left / HORIZ_INTERVAL;
	const int point_right = time_right / HORIZ_INTERVAL;
	
	vector<double> yv_double_invert(yv_size);
	for (int i = 0; i < yv_size; i++)
	{
		yv_double_invert[i] = -yv[i] + 2 * baseline;
	}
	std::vector<float> yv_float = TypeConvertion::GetVectorFloat(yv_double_invert);
	s = new TSpectrum();
	s->Background(&yv_float[point_left], point_right - point_left, 50, TSpectrum::kBackIncreasingWindow, TSpectrum::kBackOrder2, kTRUE, TSpectrum::kBackSmoothing3, kFALSE);

	baseline_vec = TypeConvertion::GetVectorDouble(yv_float);

	////find baseline value right before region 
	//double baseline_avr_before = 0;
	//int start_index_bl_avr = (point_left - 100) > 0 ? (point_left - 100) : 0;
	//for (int i = start_index_bl_avr; i < point_left; i++)
	//{
	//	baseline_avr_before += baseline_vec[i];
	//}
	//baseline_avr_before /= 100;

	//базовая линия будет тривиальной до точки der_max_position, где производная максимальна, а дальше будет нетривиальная до point_right
	//var1
	for (int i = 0; i < point_left; i++)
	{
		baseline_vec[i] = baseline;
	}
	////var2
	//for (int i = 0; i < der_max_position; i++)
	//{
	//	baseline_vec[i] = baseline;
	//}

	for (int i = point_right; i < yv_size; i++)
	{
		baseline_vec[i] = baseline;
	}

	


	////correction of baseline
	//const int n_ponts = 10;
	//int n_ponts_under_baseline;
	//for (int i = point_left; i <= (point_right - n_ponts); i++)
	//{
	//	//var1
	//	//if (baseline_vec[i] > 0)
	//	//{
	//	//	baseline_vec[i] = baseline_avr_before;
	//	//}

	//	////var2
	//	////если все последующие n_ponts окажутся ниже стандартной(тривиальной) базовой линии, то именно с этого момента изменить стандартную базовую линию на нетривиальную 
	//	//n_ponts_under_baseline = 0;
	//	//for (int j = i; j < (i + n_ponts); j++)
	//	//{
	//	//	const double y_tmp = yv_double_invert[j];
	//	//	n_ponts_under_baseline += (yv_double_invert[j] < baseline);
	//	//}

	//	//if ( n_ponts_under_baseline == (n_ponts) )
	//	//{
	//	//	for (int k = point_left; k < i; k++)
	//	//	{
	//	//		baseline_vec[k] = baseline;
	//	//	}

	//	//	cout << "i = "<< i << endl;
	//	//	
	//	//	break;
	//	//}
	//}
}


CalcBaselineZeroComp::~CalcBaselineZeroComp()
{
	delete s;
}
