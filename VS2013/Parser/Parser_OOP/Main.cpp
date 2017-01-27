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

	

	const string path_name = "D:\\Data_work\\161026\\run7\\";
	vector<ch_info> ch_list;
	ch_list.resize(2);

	ch_list[0].id = 1;
	ch_list[0].VERTICAL_OFFSET = -0.400000005960464;
	ch_list[0].VERTICAL_GAIN = 0.0000249887998506892;

	ch_list[1].id = 3;
	ch_list[1].VERTICAL_OFFSET = -3;
	ch_list[1].VERTICAL_GAIN = 0.000124943995615467;

	comm_info str_comm;
	str_comm.write_type = 4096;
	str_comm.time_offset = 5;//us
	str_comm.HORIZ_INTERVAL = 5;//ns per point;
	str_comm.WAVE_ARRAY_COUNT = 10002;//Total number of points

	//WriteTree *wrt = NULL;

	TTree tree_common_info("common_info", "Parser tree 2");
	double HORIZ_INTERVAL = str_comm.HORIZ_INTERVAL;
	tree_common_info.Branch("HORIZ_INTERVAL", &HORIZ_INTERVAL, "HORIZ_INTERVAL/D");
	tree_common_info.Fill();
	string str_common_info = path_name + "trees\\common_info.root";
	TFile f_tree_common_info(str_common_info.c_str(), "RECREATE");
	tree_common_info.Write();
	f_tree_common_info.Close();


	const int events_per_file = 1000;
	const int start_event_number = 1;
	const int stop_event_number = 100;
	const int n_events = stop_event_number;
	cout << "n_events = " << stop_event_number - start_event_number + 1 << endl;

	TFile *f_tree = new TFile("D:\\Data_work\\161026\\run7\\trees\\Block0000000.root", "RECREATE");
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


	double n_peaks_caen;
	tree.Branch("n_peaks_caen", &n_peaks_caen, "n_peaks_caen/D");

	int point_s2_left_caen, point_s2_right_caen;
	tree.Branch("point_s2_left_caen", &point_s2_left_caen, "point_s2_left_caen/I");
	tree.Branch("point_s2_right_caen", &point_s2_right_caen, "point_s2_right_caen/I");

	//time
	vector<double> time;
	tree.Branch("time", &time);

	//ortec
	vector<double> data_raw_ortec;
	tree.Branch("data_raw_ortec", &data_raw_ortec);

	vector<double> data_der_ortec;
	tree.Branch("data_der_ortec", &data_der_ortec);

	vector<double> data_int_ortec;
	tree.Branch("data_int_ortec", &data_int_ortec);


	//caen
	vector<double> data_raw_caen;
	tree.Branch("data_raw_caen", &data_raw_caen);

	vector<double> data_der_caen;
	tree.Branch("data_der_caen", &data_der_caen);

	vector<double> data_smooth_caen;
	tree.Branch("data_smooth_caen", &data_smooth_caen);

	vector<double> data_int_caen;
	tree.Branch("data_int_caen", &data_int_caen);

	vector<int> peak_position_caen;
	tree.Branch("peak_position_caen", &peak_position_caen);

	vector<double> baseline_vec_caen;
	tree.Branch("baseline_vec_caen", &baseline_vec_caen);

	double integral_s1_caen;
	tree.Branch("integral_s1_caen", &integral_s1_caen);

	double integral_s2_caen;
	tree.Branch("integral_s2_caen", &integral_s2_caen);


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
		baseline_vec_caen = calc_data.GetBaselineVec()[1];

		min_ch0 = calc_data.GetMin()[0];
		min_ch1 = calc_data.GetMin()[1];

		max_ch0 = calc_data.GetMax()[0];
		max_ch1 = calc_data.GetMax()[1];

		n_peaks_caen = (calc_data.GetPeakPosition()[1]).size();
		point_s2_left_caen = calc_data.GetPointS2Left();
		point_s2_right_caen = calc_data.GetPointS2Right();

		time = calc_data.GetTime();

		data_raw_caen = calc_data.GetData()[1];
		data_der_caen = calc_data.GetDer()[1];
		data_smooth_caen = calc_data.GetSmooth()[1];
		data_int_caen = calc_data.GetInt()[1];
		peak_position_caen = calc_data.GetPeakPosition()[1];

		data_raw_ortec = calc_data.GetData()[0];
		data_der_ortec = calc_data.GetDer()[0];
		data_int_ortec = calc_data.GetInt()[0];

		integral_s1_caen = calc_data.GetIntegralS1()[1];
		integral_s2_caen = calc_data.GetIntegralS2()[1];

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

		//ofstream file_out(path_name + "file.txt");
		//for (int k = 0; k < rdt.GetTimeArray().size(); k++)
		//{
		//	file_out << rdt.GetTimeArray()[k] << "\t" << rdt.GetDataDouble()[1][k]  << endl;
		//}

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