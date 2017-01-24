#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

#include "ReadData.h"
#include "WriteTree.h"
#include "CalcData.h"

#include "TApplication.h"
#include "TROOT.h"

using namespace std;

int main(int argc, char *argv[])
{
	clock_t t_total = clock();
	clock_t t_read_file = 0;
	clock_t t_calc_data = 0;
	clock_t t_fill_canv = 0;
	clock_t t_tree_write = 0;
	clock_t t_f_tree_close = 0;
	clock_t t_tree_fill = 0;
	clock_t t_before;
	clock_t t_after;
	
	
	TApplication theApp("theApp", &argc, argv);//let's add some magic! https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=22972
	gROOT->SetBatch(kTRUE);

	

	const string path_name = "D:\\Data_work\\161026\\run3\\";
	vector<ch_info> ch_list;
	ch_list.resize(2);

	ch_list[0].id = 1;
	ch_list[0].VERTICAL_OFFSET = -0.294999986886978;
	ch_list[0].VERTICAL_GAIN = 0.0000124943999253446;

	ch_list[1].id = 3;
	ch_list[1].VERTICAL_OFFSET = -3.04999995231628;
	ch_list[1].VERTICAL_GAIN = 0.000124943995615467;

	comm_info str_comm;
	str_comm.write_type = 4096;
	str_comm.time_offset = 40;//us
	str_comm.HORIZ_INTERVAL = 5;//ns per point;


	//WriteTree *wrt = NULL;

	const int events_per_file = 1000;
	const int start_event_number = 1;
	const int stop_event_number = 10;
	const int n_events = stop_event_number;
	cout << "n_events = " << n_events << endl;

	TFile *f_tree = new TFile("D:\\Data_work\\161026\\run3\\trees\\Block0000000.root", "RECREATE");
	TTree tree("t1", "Parser tree");

	double baseline_ch0, baseline_ch1;
	tree.Branch("baseline_ch0", &baseline_ch0, "baseline_ch0/D");
	tree.Branch("baseline_ch1", &baseline_ch1, "baseline_ch1/D");

	double min_ch0, min_ch1;
	tree.Branch("min_ch0", &min_ch0, "min_ch0/D");
	tree.Branch("min_ch1", &min_ch1, "min_ch1/D");

	double max_ch0, max_ch1;
	tree.Branch("max_ch0", &max_ch0, "max_ch0/D");
	tree.Branch("max_ch1", &max_ch1, "max_ch1/D");

	//TCanvas canv;
	//tree.Branch("canvas", "TCanvas", &canv);


	for (int event_number = start_event_number; event_number <= stop_event_number; event_number++)
	{
		t_before = clock();
		ReadData rdt(path_name, event_number, ch_list, str_comm);
		t_after = clock();
		t_read_file += t_after - t_before;

		t_before = clock();
		CalcData calc_data(rdt.GetDataDouble(), rdt.GetTimeArray());
		t_after = clock();
		t_calc_data += t_after - t_before;

		t_before = clock();
		FillCanv fill_canv(calc_data);
		t_after = clock();
		t_fill_canv += t_after - t_before;

		baseline_ch0 = calc_data.GetBaseline()[0];
		baseline_ch1 = calc_data.GetBaseline()[1];

		min_ch0 = calc_data.GetMin()[0];
		min_ch1 = calc_data.GetMin()[1];

		max_ch0 = calc_data.GetMax()[0];
		max_ch1 = calc_data.GetMax()[1];

		//canv = &(fill_canv.GetCanv()).Copy;
		//tree.Branch("canvas", "TCanvas", &( fill_canv.GetCanv() ) );//this work incorect

		t_before = clock();
		tree.Fill();
		t_after = clock();
		t_tree_fill += t_after - t_before;

		//if ( (event_number - start_event_number) % events_per_file == 0)
		//	wrt = new WriteTree(path_name + "trees\\");

		//wrt->Fill(calc_data, fill_canv);

		//if ( ((event_number - start_event_number) % events_per_file == events_per_file - 1) || (event_number == stop_event_number) )
		//	delete wrt;

		if(event_number % 10 == 0)
			cout << "event_number = " << event_number << endl;
	}

	t_before = clock();
	tree.Write();
	t_after = clock();
	t_tree_write += t_after - t_before;

	t_before = clock();
	f_tree->Close();
	t_after = clock();
	t_f_tree_close += t_after - t_before;

	cout << "t_read_file[ms] = " << (double)(t_read_file) / (CLOCKS_PER_SEC * n_events) * 1000 << endl;
	cout << "t_calc_data[ms] = " << (double)(t_calc_data) / (CLOCKS_PER_SEC * n_events) * 1000 << endl;
	cout << "t_fill_canv[ms] = " << (double)(t_fill_canv) / (CLOCKS_PER_SEC * n_events) * 1000 << endl;
	cout << "t_tree_write[ms] = " << (double)(t_tree_write) / (CLOCKS_PER_SEC * n_events) * 1000 << endl;
	cout << "t_f_tree_close[ms] = " << (double)(t_f_tree_close) / (CLOCKS_PER_SEC * n_events) * 1000 << endl;
	cout << "t_tree_fill[ms] = " << (double)(t_tree_fill) / (CLOCKS_PER_SEC * n_events) * 1000 << endl;
	cout << "t_total[ms] = " << (double)(clock() - t_total) / (CLOCKS_PER_SEC * n_events) * 1000 << endl;

	cout << "all is ok" << endl;
	system("pause");
	theApp.Terminate();
	theApp.Run();
	return 0;
}