#pragma once

#include "TCanvas.h"
#include "TGraph.h"
#include "TF1.h"

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
	std::vector<double> peak_position_caen;
};

class FormCanv
{
public:
	FormCanv(Data &data);
	~FormCanv();
	TCanvas& GetCanv();
private:
	TCanvas canv;

	TGraph *graph_1;
	TGraph *graph_2;
	TGraph *graph_2_2;
	TGraph *graph_3;
	TGraph *graph_4;
	TGraph *graph_5;
	TGraph *graph_6;

	TF1 *tf1_baseline_cd1;
	TF1 *tf1_baseline_cd2;
};

