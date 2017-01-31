#include "FormCanv.h"

#include <algorithm>
#include <iostream>

#include "TGraph.h"
#include "TAxis.h"


using namespace std;

FormCanv::FormCanv(Data &data) : canv("c", "c", 0, 0, 1900, 900)
{
	canv.Divide(2, 2);
	canv.SetGrid();

	const double max_time = *max_element((data.time).begin(), (data.time).end());

	//canv.cd(1);
	//graph_1 = new TGraph(data.data_raw_ortec.size(), &data.time[0], &data.data_raw_ortec[0]);
	//graph_1->SetTitle("Signal from Ortec");
	//graph_1->GetXaxis()->SetTitle("Time [ns]");
	//graph_1->GetYaxis()->SetTitle("Amplitude [mV]");
	//graph_1->Draw("apl");

	//tf1_baseline_cd1 = new TF1("tf1_baseline_cd1", "[0]", 0, max_time);
	//tf1_baseline_cd1->SetParameter(0, data.baseline_ch0);
	//tf1_baseline_cd1->Draw("same");

	canv.cd(1);
	graph_2 = new TGraph(data.data_raw_caen.size(), &data.time[0], &data.data_raw_caen[0]);
	graph_2->SetTitle("Signal from CAEN");
	graph_2->GetXaxis()->SetTitle("Time [ns]");
	graph_2->GetYaxis()->SetTitle("Amplitude [mV]");
	graph_2->Draw("apl");

	tf1_baseline_cd2 = new TF1("tf1_baseline_cd2", "[0]", 0, max_time);
	tf1_baseline_cd2->SetParameter(0, data.baseline_ch1);
	tf1_baseline_cd2->Draw("same");

	graph_2_3 = new TGraph(data.baseline_vec_caen.size(), &data.time[0], &data.baseline_vec_caen[0]);
	graph_2_3->SetLineColor(kGreen);
	graph_2_3->Draw("same");

	vector<double> data_raw_caen_peak_val;
	vector<double> data_raw_caen_peak_time;
	data_raw_caen_peak_val.resize(data.peak_position_caen.size());
	data_raw_caen_peak_time.resize(data.peak_position_caen.size());
	for (int i = 0; i < data.peak_position_caen.size(); i++)
	{
		data_raw_caen_peak_val[i] = 0;//data.data_raw_caen[data.peak_position_caen[i]];
		data_raw_caen_peak_time[i] = data.peak_position_caen[i] * data.HORIZ_INTERVAL;
	}
	graph_2_2 = new TGraph(data_raw_caen_peak_time.size(), &data_raw_caen_peak_time[0], &data_raw_caen_peak_val[0]);
	graph_2_2->SetMarkerStyle(20);
	graph_2_2->SetMarkerSize(1);
	graph_2_2->SetMarkerColor(kBlue);
	graph_2_2->Draw("same p");

	//graph_2_4 = new TGraph(data.time.size(), &data.time[0], &data.data_smooth_caen[0]);
	//graph_2_4->SetLineColor(kMagenta);
	//graph_2_4->Draw("same l");

	//vector<double> data_min_baseline(data.time.size());
	//for (int i = 0; i < data.time.size(); i++)	{ data_min_baseline[i] = data.data_raw_caen[i] - data.baseline_vec_caen[i]; }
	//graph_2_4 = new TGraph(data.time.size(), &data.time[0], &data_min_baseline[0]);
	//graph_2_4->SetLineColor(kMagenta);
	//graph_2_4->Draw("same l");


	string text_integral_s1 = "integral s1[mV * mS] = " + to_string(data.integral_s1_caen / 1E6);
	string text_integral_s2 = "integral s2[mV * mS] = " + to_string(data.integral_s2_caen / 1E6);
	pt_cd1 = new TPaveText(0.8, 0.8, 1, 1, "nbNDC");
	pt_cd1->AddText(text_integral_s1.c_str());
	pt_cd1->AddText(text_integral_s2.c_str());
	pt_cd1->Draw();

	//graph_1_1 = new TGraph(data.yv_cut_caen.size(), &data.time[0], &data.yv_cut_caen[0]);
	//graph_1_1->SetLineColor(kRed);
	//graph_1_1->SetMarkerColor(kBlack);
	//graph_1_1->SetMarkerStyle(20);
	//graph_1_1->SetMarkerSize(0.5);
	//graph_1_1->Draw("same lp");


	canv.cd(2);
	hist_1 = new TH1F("h1", "h1 title", 20, 0, max_time);
	for (int i = 0; i < data.peak_position_caen.size(); i++){ hist_1->Fill(data.peak_position_caen[i] * data.HORIZ_INTERVAL); }
	hist_1->Draw();

	//canv.cd(3);
	//graph_3 = new TGraph(data.data_der_ortec.size(), &data.time[0], &data.data_der_ortec[0]);
	//graph_3->SetTitle("Derivative from Ortec signal");
	//graph_3->GetXaxis()->SetTitle("Time [ns]");
	//graph_3->GetYaxis()->SetTitle("Derivative [mV / ns]");
	//graph_3->Draw("apl");

	canv.cd(3);
	graph_4 = new TGraph(data.data_der_caen.size(), &data.time[0], &data.data_der_caen[0]);
	graph_4->SetTitle("Derivative from CAEN signal");
	graph_4->GetXaxis()->SetTitle("Time [ns]");
	graph_4->GetYaxis()->SetTitle("Derivative [mV / ns]");
	graph_4->Draw("apl");

	//show s2 region
	f1 = new TF1("f1", "[0]", data.point_s2_left_caen * data.HORIZ_INTERVAL, data.point_s2_right_caen * data.HORIZ_INTERVAL);
	f1->SetParameter(0, 0);
	f1->SetLineColor(kOrange);
	f1->Draw("same f");

	vector<double> data_der_caen_peak_val;
	vector<double> data_der_caen_peak_time;
	data_der_caen_peak_val.resize(data.peak_position_caen.size());
	data_der_caen_peak_time.resize(data.peak_position_caen.size());
	for (int i = 0; i < data.peak_position_caen.size(); i++)
	{
		data_der_caen_peak_val[i] = data.data_der_caen[data.peak_position_caen[i]];
		data_der_caen_peak_time[i] = data.peak_position_caen[i] * data.HORIZ_INTERVAL;
	}
	graph_2_2 = new TGraph(data_der_caen_peak_time.size(), &data_der_caen_peak_time[0], &data_der_caen_peak_val[0]);
	graph_2_2->SetMarkerStyle(20);
	graph_2_2->SetMarkerSize(1);
	graph_2_2->SetMarkerColor(kBlue);
	graph_2_2->Draw("same p");

	//canv.cd(5);
	//graph_5 = new TGraph(data.data_int_ortec.size(), &data.time[0], &data.data_int_ortec[0]);
	//graph_5->SetTitle("Inttegral from Ortec signal");
	//graph_5->GetXaxis()->SetTitle("Time [ns]");
	//graph_5->GetYaxis()->SetTitle("Integral [mV * ns]");
	//graph_5->Draw("apl");

	//canv.cd(6);
	//graph_6 = new TGraph(data.data_int_caen.size(), &data.time[0], &data.data_int_caen[0]);
	//graph_6->SetTitle("Inttegral from CAEN signal");
	//graph_6->GetXaxis()->SetTitle("Time [ns]");
	//graph_6->GetYaxis()->SetTitle("Integral [mV * ns]");
	//graph_6->Draw("apl");

}


FormCanv::~FormCanv()
{
	delete graph_1;
	//delete graph_1_1;
	delete graph_2;
	delete graph_2_2;
	delete graph_2_3;
	//delete graph_2_4;
	delete graph_3;
	delete graph_4;
	delete graph_5;
	delete graph_6;

	delete hist_1;

	delete tf1_baseline_cd1;
	delete tf1_baseline_cd2;

	delete f1;
	delete pt_cd1;
}

TCanvas& FormCanv::GetCanv()
{
	return canv;
}