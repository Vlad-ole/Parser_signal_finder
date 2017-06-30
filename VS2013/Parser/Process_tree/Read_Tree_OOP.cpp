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

int main(int argc, char *argv[])
{
	const int n_tree_files = 1;
	const string path_name = "D:\\Data_work\\170622_caen_trees\\event_x-ray_18_small_2\\";

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

	int run_id;
	int ch_id;
	int event_id;
	vector<double> *data_raw = 0;
	
	chain.SetBranchAddress("data_raw", &data_raw);
	chain.SetBranchAddress("run_id", &run_id);
	chain.SetBranchAddress("ch_id", &ch_id);
	chain.SetBranchAddress("event_id", &event_id);

	const int n_events = chain.GetEntries();
	int pass_counter = 0;
	//const int n_events = 5000;
	cout << "chain.GetEntries() = " << chain.GetEntries() << endl;

	const bool simple_analysis = 1;

	vector<double> time_v;
	time_v.resize(9999);
	chain.Branch("time_v", &time_v);
	for (int i = 0; i < time_v.size(); i++)
	{
		time_v[i] = i * 16;//ns
	}	
	chain.Fill();

	if (simple_analysis)
	{
		gROOT->SetBatch(kFALSE);

		TCut total_cut = "ch_id == 32 && run_id == 2721 && event_id < 3";

		chain.SetMarkerStyle(20);
		chain.SetMarkerSize(1);

		chain.Draw("data_raw:time_v", "ch_id == 32 && run_id == 2721 && event_id == 0");
		chain.SetMarkerColor(kRed);
		chain.Draw("data_raw:time_v", "ch_id == 32 && run_id == 2721 && event_id == 1", "same");
		chain.SetMarkerColor(kGreen);
		chain.Draw("data_raw:time_v", "ch_id == 32 && run_id == 2721 && event_id == 2", "same");
	}
}