#pragma once

#include <iostream>
#include <vector>


class FTFilter
{
public:
	FTFilter(std::vector<double>& yv, const double cut_frequency_low, const double cut_frequency_high, const double time_scale);
	~FTFilter();

	std::vector<double> GetYvCut();
	std::vector<double> GetPowerSpectralDensity();
	std::vector<double> GetFrequencyV();
	//void CaclYvCut(const double cut_frequency);
private:
	std::vector<double> yv;
	std::vector<double> fft_re;
	std::vector<double> fft_im;
	std::vector<double> fft_amp;
	std::vector<double> fft_phase;
	std::vector<double> power_spectral_density;
	std::vector<double> frequency_v;

	std::vector<double> fft_re_cut;
	std::vector<double> fft_im_cut;
	std::vector<double> fft_amp_cut;
	std::vector<double> fft_phase_cut;
	std::vector<double> yv_cut;

	//methods
	double phase(const double re, const double im);
};

