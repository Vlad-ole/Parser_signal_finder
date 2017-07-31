#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

#include "ReadData.h"
#include "ReadData_CAEN.h"
#include "ReadData_LeCroy.h"

#include "WriteTree.h"
#include "CalcData.h"

#include "RunDescription.h"

#include "TApplication.h"
#include "TROOT.h"

using namespace std;

int main(int argc, char *argv[])
{
	clock_t t_total = clock();
	clock_t t_read_file = 0;
	clock_t t_calc_data = 0;
	clock_t t_tree_write = 0;
	clock_t t_f_tree_close = 0;
	clock_t t_tree_fill = 0;
	clock_t t_before;
	clock_t t_after;
	clock_t t_initialisation = 0;
	
	
	TApplication theApp("theApp", &argc, argv);//let's add some magic! https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=22972
	gROOT->SetBatch(kTRUE);

	//-------------------------------------------------
	//For CAEN
	//path_info PathInfo;
	//PathInfo.events_per_file = 10;	
	//PathInfo.events_per_file = 1000;
	
	vector<ch_info> ch_list;
	//var1
	const int n_ch = 32;
	ch_list.resize(n_ch);
	for (int i = 0; i < n_ch; i++)
	{
		/*if (i < 8) ch_list[i].id = i;
		else ch_list[i].id = i + 24;*/
		
		//ch_list[0].id = 38;
		//ch_list[i].id = i + 32;
		ch_list[i].id = GetChId(i);
	}
	

	////var2
	//const int n_ch = 1;
	//ch_list.resize(n_ch);
	//for (int i = 0; i < n_ch; i++)
	//{
	//	ch_list[0].id = 38;
	//}
	////
	
	comm_info str_comm;
	str_comm.HORIZ_INTERVAL = 16;//ns per point;
	str_comm.WAVE_ARRAY_COUNT = 9999;//number of points in one event
	//-------------------------------------------------
	

	//tree settings
	const int runs_per_tree_file = 10;
	
	//which raw files should be processed?
	//this information in RunDescription.cpp
	PathInfo.path_name = PathInfo_path_name;
	
	const int n_runs = stop_run_number;
	cout << "n_runs = " << stop_run_number - start_run_number + 1 << endl;

	TFile* f_tree = NULL;
	TTree* tree = NULL;
	int counter_f_tree = 0;

	t_initialisation = clock() - t_total;
	for (int run_number = start_run_number; run_number <= stop_run_number; run_number++)
	{
		if (run_number % 1 == 0)
			cout << "event_number = " << run_number << endl;
		
		PathInfo.run_number = run_number;

		t_before = clock();
		ReadData_CAEN rdt(PathInfo, ch_list, str_comm);
		t_after = clock();
		t_read_file += t_after - t_before;

		t_before = clock();
		vector<CalcData> calc_data_v;
		//calc_data_v.resize(PathInfo.events_per_file);
		for (int temp_event_id = 0; temp_event_id < PathInfo.events_per_file; temp_event_id++)
		{
			//CalcData calc_data(rdt.GetDataDouble()[temp_event_id], rdt.GetTimeArray());
			//calc_data_v[temp_event_id] = calc_data;
			if (temp_event_id % 10 == 0)
			{
				cout << "temp_event_id = " << temp_event_id << endl;
			}			
			calc_data_v.push_back(CalcData(rdt.GetDataDouble()[temp_event_id], rdt.GetTimeArray(), str_comm.HORIZ_INTERVAL));
		}		
		t_after = clock();
		t_calc_data += t_after - t_before;

			
		int temp_event_id;
		int ch_id;
		double min_element;
		double max_element;
		int der_min_position;
		int der_max_position;
		double baseline;
		double integral;
		vector<double> data_raw = rdt.GetDataDouble()[0][0];
		vector<double> data_smooth;
		vector<double> data_der;
		vector<double> data_int;
		vector<double> baseline_v;
		vector<double> local_baseline;
		vector<double> integral_one_peak;
		double num_of_pe_in_event;
		//vector<double> integral_one_event;
		vector<int> signals_x_start;
		vector<int> signals_x_stop;
		vector<double> double_integral_one_peak;
		vector<double> double_integral_one_peak_vec_y;
		double x_cog_position;
		double y_cog_position;
		
		//define tree
		if ((run_number - start_run_number) % runs_per_tree_file == 0)
		{
			ostringstream f_tree_name;
			f_tree_name << path_name_tree << "Block" << setfill('0') << setw(7) << counter_f_tree << ".root";
			f_tree = TFile::Open(f_tree_name.str().c_str(), "RECREATE");
			tree = new TTree("t1", "Parser tree");
			
			tree->Branch("run_id", &run_number);
			tree->Branch("event_id", &temp_event_id);
			tree->Branch("ch_id", &ch_id);
			
			tree->Branch("min_element", &min_element);
			tree->Branch("max_element", &max_element);

			tree->Branch("baseline", &baseline);
			tree->Branch("baseline_v", &baseline_v);

			tree->Branch("integral", &integral);

			tree->Branch("data_der", &data_der);
			tree->Branch("der_min_position", &der_min_position);
			tree->Branch("der_max_position", &der_max_position);

			tree->Branch("local_baseline", &local_baseline);
			tree->Branch("signals_x_start", &signals_x_start);
			tree->Branch("signals_x_stop", &signals_x_stop);
			
			tree->Branch("num_of_pe_in_event", &num_of_pe_in_event);
			tree->Branch("integral_one_peak", &integral_one_peak);
			//tree->Branch("integral_one_event", &integral_one_event);			
			tree->Branch("double_integral_one_peak", &double_integral_one_peak);
			tree->Branch("double_integral_one_peak_vec_y", &double_integral_one_peak_vec_y);

			tree->Branch("x_cog_position", &x_cog_position);
			tree->Branch("y_cog_position", &y_cog_position);
			
			//data			
			tree->Branch("data_raw", &data_raw);
			tree->Branch("data_smooth", &data_smooth);
			tree->Branch("data_int", &data_int);

		}

		t_before = clock();
		for (temp_event_id = 0; temp_event_id < PathInfo.events_per_file; temp_event_id++)
		{
			for (int ch = 0; ch < n_ch; ch++)
			{
				data_raw = rdt.GetDataDouble()[temp_event_id][ch];

				//define physical ch_id
				/*if (ch < 8) ch_id = ch;
				else ch_id = ch + 24;*/
				
				//var1
				//ch_id = ch + 32;
				ch_id = GetChId(ch);

				////var2
				//ch_id = 38;
				
				//get data from calc_data_v for each event and ch
				min_element = (calc_data_v[temp_event_id].GetMin())[ch];
				max_element = (calc_data_v[temp_event_id].GetMax())[ch];
				baseline = (calc_data_v[temp_event_id].GetBaseline())[ch];
				integral = (calc_data_v[temp_event_id].GetIntegral())[ch];
				baseline_v = (calc_data_v[temp_event_id].GetBaselineVec())[ch];
				data_der = (calc_data_v[temp_event_id].GetDer())[ch];
				der_min_position = (calc_data_v[temp_event_id].GetDerMinPosition())[ch];
				der_max_position = (calc_data_v[temp_event_id].GetDerMaxPosition())[ch];

				//data_smooth = (calc_data_v[temp_event_id].GetSmooth())[ch];
				//data_int = (calc_data_v[temp_event_id].GetInt())[ch];

				signals_x_start = (calc_data_v[temp_event_id].GetSignalsXStart())[ch];
				signals_x_stop = (calc_data_v[temp_event_id].GetSignalsXStop())[ch];
				local_baseline = (calc_data_v[temp_event_id].GetLocalBaselineV())[ch];
				integral_one_peak = (calc_data_v[temp_event_id].GetIntegralOnePeak())[ch];
				num_of_pe_in_event = (calc_data_v[temp_event_id].GetNumOfPeInEventVec())[ch];
				//integral_one_event = (calc_data_v[temp_event_id].GetIntegralOneEvent())[ch];

				double_integral_one_peak = (calc_data_v[temp_event_id].GetDoubleIntegralVec())[ch];
				double_integral_one_peak_vec_y = (calc_data_v[temp_event_id].GetDoubleIntegralVecY())[ch];

				x_cog_position = calc_data_v[temp_event_id].GetXCogPosition();
				y_cog_position = calc_data_v[temp_event_id].GetYCogPosition();

				//cout << signals_x_start[0] << "\t" << signals_x_stop[0] << endl;
				//signals_pair_values = (calc_data_v[temp_event_id].GetSignalsPairValues())[ch];
				//signals_x_values = (calc_data_v[temp_event_id].GetSignalsValues().first)[ch];
				//signals_y_values = (calc_data_v[temp_event_id].GetSignalsValues().second)[ch];

				tree->Fill();
			}
		}		
		t_after = clock();
		t_tree_fill += t_after - t_before;

		if (((run_number - start_run_number) % runs_per_tree_file == runs_per_tree_file - 1) || (run_number == stop_run_number))
		{
			t_before = clock();
			tree->Write();
			t_after = clock();
			t_tree_write += t_after - t_before;

			t_before = clock();
			f_tree->Close();
			t_after = clock();
			t_f_tree_close += t_after - t_before;

			delete f_tree;
			delete tree;
			f_tree = NULL;
			tree = NULL;

			counter_f_tree++;
		}


		
	}


	cout << "t_initialisation[ms] = " << (double)(t_initialisation) / (CLOCKS_PER_SEC) * 1000 << endl;
	cout << "t_read_file[ms] = " << (double)(t_read_file) / (CLOCKS_PER_SEC * n_runs) * 1000 << endl;
	cout << "t_calc_data[ms] = " << (double)(t_calc_data) / (CLOCKS_PER_SEC * n_runs) * 1000 << endl;
	cout << "t_tree_write[ms] = " << (double)(t_tree_write) / (CLOCKS_PER_SEC * n_runs) * 1000 << endl;
	cout << "t_f_tree_close[ms] = " << (double)(t_f_tree_close) / (CLOCKS_PER_SEC * n_runs) * 1000 << endl;
	cout << "t_tree_fill[ms] = " << (double)(t_tree_fill) / (CLOCKS_PER_SEC * n_runs) * 1000 << endl;
	cout << "t_total[ms] = " << (double)(clock() - t_total) / (CLOCKS_PER_SEC * n_runs) * 1000 << endl;

	cout << "all is ok" << endl;
	system("pause");
	theApp.Terminate();
	theApp.Run();
	return 0;
}