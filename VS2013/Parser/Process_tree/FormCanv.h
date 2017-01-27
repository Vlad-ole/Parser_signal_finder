#pragma once

#include "TCanvas.h"
#include "TGraph.h"
#include "TF1.h"
#include "TH1F.h"
#include "TPaveText.h"

#include <vector>

struct Data
{
	double baseline_ch0;
	double baseline_ch1;
	double min_ch0;
	double min_ch1;
	double max_ch0;
	double max_ch1;

	double HORIZ_INTERVAL;

	std::vector<double> time;
	std::vector<double> data_raw_ortec;
	std::vector<double> data_raw_caen;
	std::vector<double> data_der_ortec;
	std::vector<double> data_der_caen;
	std::vector<double> data_int_ortec;
	std::vector<double> data_int_caen;
	std::vector<int> peak_position_caen;
	std::vector<double> baseline_vec_caen;
	std::vector<double> data_smooth_caen;

	double integral_s1_caen;
	double integral_s2_caen;

	int point_s2_left_caen, point_s2_right_caen;
};

class FormCanv
{
public:
	FormCanv(Data &data);
	~FormCanv();
	TCanvas& GetCanv();
	void Calc();
private:
	TCanvas canv;

	TGraph *graph_1;
	TGraph *graph_2;
	TGraph *graph_2_2;
	TGraph *graph_2_3;
	TGraph *graph_2_4;
	TGraph *graph_3;
	TGraph *graph_4;
	TGraph *graph_5;
	TGraph *graph_6;
	TH1F *hist_1;

	TF1 *tf1_baseline_cd1;
	TF1 *tf1_baseline_cd2;
	TF1 *f1;

	TPaveText *pt_cd1;

	double t_0;
};

