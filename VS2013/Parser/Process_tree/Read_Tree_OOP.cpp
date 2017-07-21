#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <utility>  
#include <map>  
#include <fstream>
#include <algorithm>

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

//----------------------------
//O my God!!! I did it!
string cut_condition_srt;
bool cut_condition_bool;
#define REMEMBER_CUT(x) cut_condition_srt = #x; cut_condition_bool = x;

//----------------------------

int main(int argc, char *argv[])
{
	gROOT->SetBatch(kFALSE);
	
	const int n_tree_files = 1;
	//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_20_thmV\\";
	std::string path_name_tree = "D:\\Data_work\\170713_caen_trees\\Cd\\event_2200dVGEM_18kV_Cd\\";
	//const string path_name = "D:\\Data_work\\170622_caen_trees\\event_x-ray_4_thmV\\";
	const double HORIZ_INTERVAL = 16;

	TObjArray Hlist_gr(0);
	Hlist_gr.SetOwner(kTRUE);

	//Chain chain;
	TChain chain("t1");
	for (int i = 0; i < n_tree_files; i++)
	{
		ostringstream f_tree_name;
		f_tree_name << path_name_tree << "Block" << setfill('0') << setw(7) << i << ".root";
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
	vector<double> *data_der = 0;
	vector<double> *data_int = 0;
	vector<double> *data_smooth = 0;
	vector<double> *baseline_v = 0;
	vector<double> *local_baseline = 0;
	vector<int> *signals_x_start = 0;
	vector<int> *signals_x_stop = 0;
	vector<double> *integral_one_peak = 0;
	
	chain.SetBranchAddress("min_element", &min_element);
	chain.SetBranchAddress("max_element", &max_element);
	chain.SetBranchAddress("baseline", &baseline);
	chain.SetBranchAddress("baseline_v", &baseline_v);
	chain.SetBranchAddress("integral", &integral);
	chain.SetBranchAddress("der_min_position", &der_min_position);
	chain.SetBranchAddress("der_max_position", &der_max_position);
	chain.SetBranchAddress("local_baseline", &local_baseline);
	chain.SetBranchAddress("signals_x_start", &signals_x_start);
	chain.SetBranchAddress("signals_x_stop", &signals_x_stop);
	chain.SetBranchAddress("integral_one_peak", &integral_one_peak);

	chain.SetBranchAddress("data_raw", &data_raw);
	chain.SetBranchAddress("data_int", &data_int);
	chain.SetBranchAddress("data_smooth", &data_smooth);
	chain.SetBranchAddress("data_der", &data_der);

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
		time_v[i] = i * HORIZ_INTERVAL;//ns
	}
	chain.Fill();

	//vector<double> signals_x_values;
	//vector<double> signals_y_values;
	//vector<double> local_baseline_y_values;
	//for (int i = 0; i < n_events; i++)
	//{
	//	chain.GetEntry(i);

	//	if (i % 10 == 0)
	//	{
	//		cout << "event = " << i << endl;
	//	}

	//	REMEMBER_CUT(ch_id == 38 && run_id == 77 && event_id == 0);
	//	if (cut_condition_bool)
	//	{
	//		//signals_x_values.clear();
	//		//signals_y_values.clear();

	//		for (int j = 0; j < (*signals_x_start).size(); j++)
	//		{
	//			//COUT((*local_baseline)[j]);
	//			for (int k = (*signals_x_start)[j]; k < (*signals_x_stop)[j]; k++)
	//			{
	//				signals_x_values.push_back(k * HORIZ_INTERVAL);
	//				signals_y_values.push_back(-(*data_raw)[k] + 2 * baseline - (*baseline_v)[k]);
	//				local_baseline_y_values.push_back( (*local_baseline)[j] );
	//			}				
	//		}
	//	}
	//}

	//COUT(signals_x_values.size());
	//COUT(local_baseline_y_values.size());
	//if (signals_x_values.size() > 0)
	//{
	//	TGraph *gr = new TGraph(signals_x_values.size(), &signals_x_values[0], &signals_y_values[0]);
	//	gr->SetMarkerSize(2);
	//	gr->SetMarkerStyle(29);
	//	gr->SetMarkerColor(kRed);
	//	gr->SetTitle(cut_condition_srt.c_str());
	//	gr->Draw("AP");

	//	TGraph *gr_local_baseline = new TGraph(signals_x_values.size(), &signals_x_values[0], &local_baseline_y_values[0]);
	//	gr_local_baseline->SetMarkerSize(1);
	//	gr_local_baseline->SetMarkerStyle(20);
	//	gr_local_baseline->SetMarkerColor(kGreen);
	//	gr_local_baseline->Draw("same P");
	//}



	//TCut total_cut = "ch_id == 0 && run_id < 3000 && event_id < 10 && integral > 2E6 && integral < 5E6";
	//TCut total_cut = "ch_id == 38 && run_id < 10000 && event_id < 10 ";
	TCut total_cut = "ch_id == 38 && run_id == 77 && event_id == 500";
	//TCut total_cut = cut_condition_srt.c_str();
	//TCut total_cut = "ch_id == 38 && run_id == 3398 && event_id == 3 ";

	chain.SetMarkerStyle(20);
	chain.SetMarkerSize(1);

	//chain.Draw("integral_one_peak >> h(200, -2000, 10000)", total_cut, "L");

	//chain.Draw("data_raw:time_v", total_cut, "L");
	//chain.SetLineColor(kGreen);
	//chain.Draw("baseline:time_v", total_cut, "same L");
	//chain.SetLineColor(kRed);
	//chain.Draw("baseline_v:time_v", total_cut, "same L");

	//chain.Draw("der_max_position", total_cut, "L");

	//chain.Draw("signals_y_values:signals_x_values", total_cut, "LP");

	
	//chain.SetLineColor(kBlue);
	//chain.Draw("(data_int/5000.0):time_v", total_cut, "L same");
	////chain.Draw("(abs(data_der)*10):time_v", total_cut, "same L");
	//////chain.Draw("(-data_der + 2*baseline - baseline):time_v", total_cut, "L");
	chain.SetLineColor(kPink);
	////chain.Draw("(-data_raw + 2*baseline - baseline_v):time_v", total_cut, "same LP");
	//chain.Draw("(-data_raw + 2*baseline - baseline_v):time_v", total_cut, "LP");
	chain.Draw("(-data_raw + baseline):time_v", total_cut, "LP");

	//chain.Draw("(data_int/100.0):time_v", total_cut, "L");
	//chain.SetLineColor(kGreen);
	//chain.Draw("(-data_raw + baseline):time_v", total_cut, "same LP");

	//chain.Draw("(-data_raw + 2*baseline):time_v", total_cut, "LP");
	//	//chain.Draw("baseline:time_v", total_cut, "same L");
	//chain.SetLineColor(kRed);
	//chain.Draw("baseline_v:time_v", total_cut, "same L");
	//chain.SetLineColor(kGreen);
	//chain.Draw("(-data_smooth + 2*baseline):time_v", total_cut, "same L");

	//chain.Draw("((-data_smooth + 2*baseline) - baseline_v):time_v", total_cut, "LP");

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
	//const int point_from = time_from / HORIZ_INTERVAL;
	//const int point_to = time_to / HORIZ_INTERVAL;

	//double integral_tmp = 0;
	//for (int i = point_from; i < point_to; i++)
	//{
	//	integral_tmp += (data_raw_average[i] - baseline_v[i]);
	//}
	//integral_tmp *= HORIZ_INTERVAL;
	//
	//COUT(integral_tmp);
	//--------------------------------------

}
