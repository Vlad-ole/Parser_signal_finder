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


	//---------------------------
	//set braches
	int run_id;
	int ch_id;
	int event_id;
	double min_element;
	double max_element;
	double baseline;
	vector<double> *data_raw = 0;

	chain.SetBranchAddress("min_element", &min_element);
	chain.SetBranchAddress("max_element", &max_element);
	chain.SetBranchAddress("baseline", &baseline);

	chain.SetBranchAddress("data_raw", &data_raw);

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
		time_v[i] = i * 16;//ns
	}
	chain.Fill();

	gROOT->SetBatch(kFALSE);

	TCut total_cut = "ch_id == 32 && run_id == 2721 && event_id < 3";

	chain.SetMarkerStyle(20);
	chain.SetMarkerSize(1);

	chain.Draw("data_raw:time_v", "ch_id == 0 && run_id == 2721 && event_id == 0");

	//chain.Draw("max_element:event_id", "ch_id == 0 && run_id == 2721");
	//chain.SetMarkerColor(kRed);
	//chain.Draw("min_element:event_id", "ch_id == 0 && run_id == 2721");

	for (int i = 0; i < 1; i++)
	{
		chain.GetEntry(i);
		if (i % 10 == 0)
		{
			cout << "event = " << i << endl;
		}

		COUT(max_element);
		COUT(min_element);
		COUT(baseline);
	}

}
