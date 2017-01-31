#include "FTFilter.h"
#include "TMath.h"

#include "fftw3.h"
#include "TVirtualFFT.h"

using namespace std;

FTFilter::FTFilter(std::vector<double>& yv, const double cut_frequency_low, const double cut_frequency_high, const double time_scale) : yv(yv)
{
	int n_size_raw = yv.size();	
	const int n_size_fft = n_size_raw / 2 + 1;
	//const double time_scale = (yv[1] - yv[0]);
	const double sampling_frequency = 1000.0 / time_scale;//MHz
	const double delta_frequency = sampling_frequency / n_size_raw;
	const double time_from = 0;
	const double time_to = n_size_raw * time_scale;


	//calc fft transform
	TVirtualFFT *fft_own = TVirtualFFT::FFT(1, &n_size_raw, "R2C ES K");
	if (!fft_own)
	{
		cout << "error in fft!" << endl;
		system("pause");
		exit(1);
	}
	fft_re.resize(n_size_fft);
	fft_im.resize(n_size_fft);
	fft_own->SetPoints(&yv[0]);
	fft_own->Transform();
	fft_own->GetPointsComplex(&fft_re[0], &fft_im[0]);
	delete fft_own;

	//re and im -> amp and phase; cacl power_spectral_density
	frequency_v.resize(n_size_fft);
	fft_amp.resize(n_size_fft);
	fft_phase.resize(n_size_fft);
	power_spectral_density.resize(n_size_fft);
	for (int i = 0; i < n_size_fft; ++i)
	{
		frequency_v[i] = i * delta_frequency;
		fft_amp[i] = sqrt(fft_re[i] * fft_re[i] + fft_im[i] * fft_im[i]);
		power_spectral_density[i] = (fft_re[i] * fft_re[i] + fft_im[i] * fft_im[i]) / (time_to - time_from);
		fft_phase[i] = phase(fft_re[i], fft_im[i]);
	}

	//cut spectrum
	fft_amp_cut.resize(n_size_fft);
	fft_phase_cut.resize(n_size_fft);
	for (int i = 0; i < n_size_fft; i++)//pass filter
	{
		fft_amp_cut[i] = ((frequency_v[i] > cut_frequency_high) || (frequency_v[i] < cut_frequency_low)) ? 0 : fft_amp[i];
		fft_phase_cut[i] = fft_phase[i];//just dummy
	}


	//calc inverse ft
	yv_cut.resize(n_size_raw);
	fft_re_cut.resize(n_size_fft);
	fft_im_cut.resize(n_size_fft);
	for (int i = 0; i < n_size_fft; ++i)
	{
		fft_re_cut[i] = fft_amp_cut[i] * cos(fft_phase_cut[i]);
		fft_im_cut[i] = fft_amp_cut[i] * sin(fft_phase_cut[i]);
	}
	TVirtualFFT *fft_back = TVirtualFFT::FFT(1, &n_size_raw, "C2R M K");
	fft_back->SetPointsComplex(&fft_re_cut[0], &fft_im_cut[0]);
	fft_back->Transform();
	for (int i = 0; i < n_size_raw; ++i)
	{
		yv_cut[i] = (fft_back->GetPointReal(i)) / n_size_raw;
	}

	delete fft_back;

}


FTFilter::~FTFilter()
{
}

std::vector<double> FTFilter::GetYvCut()
{
	return yv_cut;
}

std::vector<double> FTFilter::GetPowerSpectralDensity()
{
	return power_spectral_density;
}

std::vector<double> FTFilter::GetFrequencyV()
{
	return frequency_v;
}


double FTFilter::phase(const double x, const double y)
{
	double result = 0;

	if (x > 0)result = atan(y / x);
	else if (x < 0 && y >= 0) result = atan(y / x) + TMath::Pi();
	else if (x < 0 && y < 0) result = atan(y / x) - TMath::Pi();
	else if (x == 0 && y > 0) result = TMath::Pi() / 2;
	else if (x == 0 && y < 0) result = -TMath::Pi() / 2;

	return result;
}