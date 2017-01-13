#include "FillCanv.h"
#include "TGraph.h"


FillCanv::FillCanv(std::vector< std::vector<double> > data, std::vector<double> time) : canv("c", "c", 0, 0, 1900, 1500)
{
	canv.Divide(2, 2);
	graph = new TGraph(data[0].size(), &time[0], &data[0][0]);
	canv.cd(1);
	graph->Draw("apl");
}


FillCanv::~FillCanv()
{
	delete graph;
}

TCanvas &FillCanv::GetCanv()
{
	return canv;
}
