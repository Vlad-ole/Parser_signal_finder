#include "FillCanv.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TF1.h"

#include <iostream>
#include <algorithm>
using namespace std;

FillCanv::FillCanv(CalcData& calc_data) : canv("c", "c", 0, 0, 1900, 1000)
{
	canv.Divide(2, 2);
	canv.SetGrid();

	const double max_time = *max_element( (calc_data.GetTime()).begin(), (calc_data.GetTime()).end());

	canv.cd(1);
	graph_1 = new TGraph(calc_data.GetData()[0].size(), &calc_data.GetTime()[0], &calc_data.GetData()[0][0]);
	graph_1->SetTitle("Signal from Ortec");
	graph_1->GetXaxis()->SetTitle("Time [ns]");
	graph_1->GetYaxis()->SetTitle("Amplitude [mV]");
	graph_1->Draw("apl");

	tf1_baseline_cd1 = new TF1("tf1_baseline_cd1", "[0]", 0, max_time);
	tf1_baseline_cd1->SetParameter(0, 0);
	tf1_baseline_cd1->Draw("same");

	canv.cd(2);
	graph_2 = new TGraph(calc_data.GetData()[1].size(), &calc_data.GetTime()[0], &calc_data.GetData()[1][0]);
	graph_2->SetTitle("Signal from CAEN");
	graph_2->GetXaxis()->SetTitle("Time [ns]");
	graph_2->GetYaxis()->SetTitle("Amplitude [mV]");
	graph_2->Draw("apl");

	tf1_baseline_cd2 = new TF1("tf1_baseline_cd2", "[0]", 0, max_time);
	tf1_baseline_cd2->SetParameter(0, 0);
	tf1_baseline_cd2->Draw("same");

	canv.cd(4);
	graph_4 = new TGraph(calc_data.GetDer()[1].size(), &calc_data.GetTime()[0], &calc_data.GetDer()[1][0]);
	graph_4->SetTitle("Der CAEN");
	graph_4->GetXaxis()->SetTitle("Time [ns]");
	graph_4->GetYaxis()->SetTitle("Derivative [mV / ns]");
	graph_4->Draw("apl");

}


FillCanv::~FillCanv()
{
	delete graph_1;
	delete graph_2;
	delete graph_3;
	delete tf1_baseline_cd1;
	delete tf1_baseline_cd2;
}

TCanvas &FillCanv::GetCanv()
{
	return canv;
}
