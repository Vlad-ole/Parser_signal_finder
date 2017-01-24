#pragma once

#include "TCanvas.h"
#include "TGraph.h"

#include "CalcData.h"

class FillCanv
{
public:
	FillCanv(CalcData& calc_data);
	~FillCanv();
	TCanvas& GetCanv();
private:
	TCanvas canv;
	TGraph *graph_1;
	TGraph *graph_2;
	TGraph *graph_3;
	TGraph *graph_4;

	TF1 *tf1_baseline_cd1;
	TF1 *tf1_baseline_cd2;
};

