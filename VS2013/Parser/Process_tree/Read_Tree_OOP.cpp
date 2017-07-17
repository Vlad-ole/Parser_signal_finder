#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>


#include "TApplication.h"
#include "TROOT.h"
#include "TObjArray.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TCut.h"


#include "FormCanv.h"
using namespace std;

#define COUT(x) cout << #x " = " << x << endl;

int main(int argc, char *argv[])
{
	const int n_tree_files = 1;
	const string path_name = "D:\\Data_work\\170622_caen_trees\\event_x-ray_20_thmV\\";
	const double time_scale = 16;

	TObjArray Hlist_gr(0);
	Hlist_gr.SetOwner(kTRUE);

	//Chain chain;
	TChain chain("t1");
	for (int i = 0; i < n_tree_files; i++)
	{
		ostringstream f_tree_name;
		f_tree_name << path_name << "Block" << setfill('0') << setw(7) << i << ".root";
		chain.Add(f_tree_name.str().c_str());
	}


	//---------------------------
	//set braches
	int run_id;
	int ch_id;
	int event_id;
	double min_element;
	double max_element;
	double baseline;
	double integral;
	int der_min_position;
	int der_max_position;
	vector<double> *data_raw = 0;
	vector<double> *der_v = 0;
	vector<double> *baseline_v = 0;
	vector<double> *data_smooth = 0;
	
	chain.SetBranchAddress("min_element", &min_element);
	chain.SetBranchAddress("max_element", &max_element);
	chain.SetBranchAddress("baseline", &baseline);
	chain.SetBranchAddress("baseline_v", &baseline_v);
	chain.SetBranchAddress("integral", &integral);
	chain.SetBranchAddress("der_min_position", &der_min_position);
	chain.SetBranchAddress("der_max_position", &der_max_position);

	chain.SetBranchAddress("data_raw", &data_raw);
	chain.SetBranchAddress("data_smooth", &data_smooth);

	chain.SetBranchAddress("run_id", &run_id);
	chain.SetBranchAddress("ch_id", &ch_id);
	chain.SetBranchAddress("event_id", &event_id);
	//---------------------------

	const int n_events = chain.GetEntries();
	int pass_counter = 0;
	//const int n_events = 5000;
	cout << "chain.GetEntries() = " << chain.GetEntries() << endl;

	vector<double> time_v;
	time_v.resize(9999);
	chain.Branch("time_v", &time_v);
	for (int i = 0; i < time_v.size(); i++)
	{
		time_v[i] = i * time_scale;//ns
	}
	chain.Fill();

	gROOT->SetBatch(kFALSE);

	//TCut total_cut = "ch_id == 0 && run_id < 3000 && event_id < 10 && integral > 2E6 && integral < 5E6";
	//TCut total_cut = "ch_id == 38 && run_id < 10000 && event_id < 10 ";
	TCut total_cut = "ch_id == 38 && run_id == 2756 && event_id == 2 ";

	chain.SetMarkerStyle(20);
	chain.SetMarkerSize(1);

	//chain.Draw("data_raw:time_v", total_cut, "L");
	//chain.SetLineColor(kGreen);
	//chain.Draw("baseline:time_v", total_cut, "same L");
	//chain.SetLineColor(kRed);
	//chain.Draw("baseline_v:time_v", total_cut, "same L");

	//chain.Draw("der_max_position", total_cut, "L");

	//chain.Draw("der_v:time_v", total_cut, "L");
	//chain.SetLineColor(kPink);
	//chain.Draw("(-data_raw + 2*baseline - baseline):time_v", total_cut, "same LP");

	chain.Draw("(-data_raw + 2*baseline):time_v", total_cut, "LP");
	chain.SetLineColor(kGreen);
	//chain.Draw("baseline:time_v", total_cut, "same L");
	//chain.SetLineColor(kRed);
	//chain.Draw("baseline_v:time_v", total_cut, "same L");
	chain.Draw("(-data_smooth + 2*baseline):time_v", total_cut, "same L");

	//chain.Draw("integral:run_id", total_cut);
	//chain.Draw("integral:event_id", total_cut);
	//chain.Draw("integral >> h(120, -350E3, 350E3)", total_cut);
	//chain.Draw("integral", total_cut);
	//chain.Draw("baseline", total_cut);
	//chain.Draw("run_id", total_cut);

	bool is_average = false;
	if (is_average)
	{
		vector<double> data_raw_average;
		data_raw_average.resize(time_v.size());
		double baseline_average = 0;

		int cut_pass_counter = 0;
		for (int i = 0; i < n_events; i++)
		{
			chain.GetEntry(i);
			if (i % 10 == 0)
			{
				cout << "event = " << i << endl;
			}

			if (ch_id == 38 /*&& integral > 100E3*/)
			{
				cut_pass_counter++;
				baseline_average += baseline;

				for (int j = 0; j < time_v.size(); j++)
				{
					data_raw_average[j] += (*data_raw)[j];
				}
			}

			//COUT(max_element);
			//COUT(min_element);
			//COUT(baseline);
			//COUT(integral);
		}

		baseline_average /= cut_pass_counter;
		for (int j = 0; j < time_v.size(); j++)
		{
			data_raw_average[j] /= cut_pass_counter;
		}
		COUT(cut_pass_counter);

		vector<double> baseline_v_avr;
		baseline_v_avr.resize(time_v.size(), baseline_average);

		TGraph *gr = new TGraph(time_v.size(), &time_v[0], &data_raw_average[0]);
		TGraph *gr_baseline = new TGraph(time_v.size(), &time_v[0], &baseline_v_avr[0]);
		gr->Draw("APL");
		gr_baseline->SetLineColor(kGreen);
		gr_baseline->Draw("same");
	}

	//--------------------------------------
	//const double time_from = 58000;
	//const double time_to = 76200;
	//const int point_from = time_from / time_scale;
	//const int point_to = time_to / time_scale;

	//double integral_tmp = 0;
	//for (int i = point_from; i < point_to; i++)
	//{
	//	integral_tmp += (data_raw_average[i] - baseline_v[i]);
	//}
	//integral_tmp *= time_scale;
	//
	//COUT(integral_tmp);
	//--------------------------------------

}
