#pragma once

#include "TCanvas.h"
#include "TGraph.h"

class FillCanv
{
public:
	FillCanv(std::vector< std::vector<double> > data, std::vector<double> time);
	~FillCanv();
	TCanvas& GetCanv();
private:
	TCanvas canv;
	TGraph *graph;
};

