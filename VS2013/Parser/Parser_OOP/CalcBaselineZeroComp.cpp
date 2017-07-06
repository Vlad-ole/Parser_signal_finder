#include "CalcBaselineZeroComp.h"
#include "TypeConvertion.h"

CalcBaselineZeroComp::CalcBaselineZeroComp(std::vector<double> yv, const int point_s2_left, const int point_s2_right)
{
	const int yv_size = yv.size();
	baseline_vec.resize(yv_size);

	s = new TSpectrum();
	std::vector<float> yv_float = TypeConvertion::GetVectorFloat(yv);
	s->Background(&yv_float[0], yv_size, 50, TSpectrum::kBackDecreasingWindow, TSpectrum::kBackOrder2, kTRUE, TSpectrum::kBackSmoothing3, kFALSE);

	baseline_vec = TypeConvertion::GetVectorDouble(yv_float);

	//find baseline value right before s2 region 
	double baseline_avr_before_s2 = 0;
	int start_index_bl_avr = (point_s2_left - 100) > 0 ? (point_s2_left - 100) : 0;
	for (int i = start_index_bl_avr; i < point_s2_left; i++)
	{
		baseline_avr_before_s2 += baseline_vec[i];
	}
	baseline_avr_before_s2 /= 100;

	//correction of baseline for s2 region
	for (int i = point_s2_left; i <= point_s2_right; i++)
	{
		if (baseline_vec[i] > 0)
		{
			baseline_vec[i] = baseline_avr_before_s2;
		}
	}
}


CalcBaselineZeroComp::~CalcBaselineZeroComp()
{
	delete s;
}
