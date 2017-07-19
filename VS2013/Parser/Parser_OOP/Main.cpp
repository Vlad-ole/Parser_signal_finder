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
	path_info PathInfo;
	
	//PathInfo.path_name = "D:\\Data_work\\test_folder\\";
	PathInfo.events_per_file = 10;	
	
	vector<ch_info> ch_list;
	const int n_ch = 1;
	ch_list.resize(n_ch);
	for (int i = 0; i < n_ch; i++)
	{
		/*if (i < 8) ch_list[i].id = i;
		else ch_list[i].id = i + 24;*/
		ch_list[0].id = 38;
	}
	
	comm_info str_comm;
	str_comm.HORIZ_INTERVAL = 16;//ns per point;
	str_comm.WAVE_ARRAY_COUNT = 9999;//number of points in one event
	//-------------------------------------------------
	

	//tree settings
	const int runs_per_tree_file = 1000;
	

	//which raw files should be processed?
	
	string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_20_thmV\\";
	PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_20_thmV\\";
	const int start_run_number = 2749;
	const int stop_run_number = 2782;
	//const int start_run_number = 2752;
	//const int stop_run_number = 2752;

	//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x_ray_18_2mmColl\\";
	//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x_ray_18_2mmColl\\";
	//const int start_run_number = 3537;
	//const int stop_run_number = 3955;

	//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_18_small_2\\";
	//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_18_small_2\\";
	//const int start_run_number = 2721;
	//const int stop_run_number = 2748;
	
	//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_16_thmV\\";
	//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_16_thmV\\";
	//const int start_run_number = 2783;
	//const int stop_run_number = 2853;

	//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_14_thmV\\";
	//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_14_thmV\\";
	//const int start_run_number = 2854;
	//const int stop_run_number = 2914;

	//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_12_thmV\\";
	//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_12_thmV\\";
	//const int start_run_number = 2915;
	//const int stop_run_number = 2953;

	//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_10_thmV\\";
	//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_10_thmV\\";
	//const int start_run_number = 2954;
	//const int stop_run_number = 3033;

	//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_10_thmV_recalib\\";
	//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_10_thmV_recalib\\";
	//const int start_run_number = 3034;
	//const int stop_run_number = 3067;

	//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_9_thmV\\";
	//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_9_thmV\\";
	//const int start_run_number = 3068;
	//const int stop_run_number = 3108;

	//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_8_thmV\\";
	//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_8_thmV\\";
	//const int start_run_number = 3109;
	//const int stop_run_number = 3168;

	//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_7_thmV\\";
	//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_7_thmV\\";
	//const int start_run_number = 3169;
	//const int stop_run_number = 3226;

	//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_5_thmV\\";
	//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_5_thmV\\";
	//const int start_run_number = 3292;
	//const int stop_run_number = 3395;

	//string path_name_tree = "D:\\Data_work\\170622_caen_trees\\event_x-ray_4_thmV\\";
	//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_4_thmV\\";
	//const int start_run_number = 3396;
	//const int stop_run_number = 3536;
	//

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
			//cout << "temp_event_id = " << temp_event_id << endl;
			calc_data_v.push_back(CalcData(rdt.GetDataDouble()[temp_event_id], rdt.GetTimeArray(), str_comm.HORIZ_INTERVAL));
		}		
		t_after = clock();
		t_calc_data += t_after - t_before;

			
		//double baseline_ch0 = calc_data.GetBaseline()[0];
		//double baseline_ch1 = calc_data.GetBaseline()[1];
		//double min_ch0 = calc_data.GetMin()[0];
		//double min_ch1 = calc_data.GetMin()[1];
		//double max_ch0 = calc_data.GetMax()[0];
		//double max_ch1 = calc_data.GetMax()[1];
		//double n_peaks_caen = (calc_data.GetPeakPosition()[1]).size();
		//int point_s2_left_caen = calc_data.GetPointS2Left();
		//int point_s2_right_caen = calc_data.GetPointS2Right();
		//vector<double> data_raw_ortec = calc_data.GetData()[0];
		//vector<double> data_der_ortec = calc_data.GetDer()[0];
		//vector<double> data_int_ortec = calc_data.GetInt()[0];
		//vector<double> data_raw_caen = calc_data.GetData()[1];
		//vector<double> data_der_caen = calc_data.GetDer()[1];
		////vector<double> data_smooth_caen = calc_data.GetSmooth()[1];
		//vector<double> data_int_caen = calc_data.GetInt()[1];
		//vector<int> peak_position_caen = calc_data.GetPeakPosition()[1];
		//vector<double> baseline_vec_caen = calc_data.GetBaselineVec()[1];
		//double integral_s1_caen = calc_data.GetIntegralS1()[1];
		//double integral_s2_caen = calc_data.GetIntegralS2()[1];
		//vector<double> yv_cut_caen = calc_data.GetYvCut();
		//double integral_s1_caen_outside_the_trigger = calc_data.GetIntegral_s1_caen_outside_the_trigger();

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
		vector<int> signals_x_start;
		vector<int> signals_x_stop;
		//vector< pair<int, int> > signals_pair_values;
		//std::vector< std::vector<int> > signals_position_values;//root does not know how to work with this object ()
		//vector<double> signals_x_values;
		//vector<double> signals_y_values;

		//vector<double> time = rdt.GetTimeArray();
		
		//define tree
		if ((run_number - start_run_number) % runs_per_tree_file == 0)
		{
			ostringstream f_tree_name;
			f_tree_name << path_name_tree << "Block" << setfill('0') << setw(7) << counter_f_tree << ".root";
			f_tree = TFile::Open(f_tree_name.str().c_str(), "RECREATE");
			tree = new TTree("t1", "Parser tree");
			
			//tree->Branch("baseline_ch0", &baseline_ch0, "baseline_ch0/D");
			//tree->Branch("baseline_ch1", &baseline_ch1, "baseline_ch1/D");			
			//tree->Branch("min_ch0", &min_ch0, "min_ch0/D");
			//tree->Branch("min_ch1", &min_ch1, "min_ch1/D");			
			//tree->Branch("max_ch0", &max_ch0, "max_ch0/D");
			//tree->Branch("max_ch1", &max_ch1, "max_ch1/D");
			//tree->Branch("n_peaks_caen", &n_peaks_caen, "n_peaks_caen/D");			
			//tree->Branch("point_s2_left_caen", &point_s2_left_caen, "point_s2_left_caen/I");
			//tree->Branch("point_s2_right_caen", &point_s2_right_caen, "point_s2_right_caen/I");
			//tree->Branch("time", &time);
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
			tree->Branch("signals_x_start", &signals_x_start);
			tree->Branch("signals_x_stop", &signals_x_stop);
			
			//tree->Branch("signals_position_values", &signals_position_values);
			//tree->Branch("signals_pair_values", &signals_pair_values);
			//tree->Branch("signals_x_values", &signals_x_values);
			//tree->Branch("signals_y_values", &signals_y_values);
	
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
				ch_id = 38;

				//get data from calc_data_v for each event and ch
				min_element = (calc_data_v[temp_event_id].GetMin())[ch];
				max_element = (calc_data_v[temp_event_id].GetMax())[ch];
				baseline = (calc_data_v[temp_event_id].GetBaseline())[ch];
				integral = (calc_data_v[temp_event_id].GetIntegral())[ch];
				baseline_v = (calc_data_v[temp_event_id].GetBaselineVec())[ch];
				data_der = (calc_data_v[temp_event_id].GetDer())[ch];
				der_min_position = (calc_data_v[temp_event_id].GetDerMinPosition())[ch];
				der_max_position = (calc_data_v[temp_event_id].GetDerMaxPosition())[ch];
				data_smooth = (calc_data_v[temp_event_id].GetSmooth())[ch];
				data_int = (calc_data_v[temp_event_id].GetInt())[ch];
				signals_x_start = (calc_data_v[temp_event_id].GetSignalsXStart())[ch];
				signals_x_stop = (calc_data_v[temp_event_id].GetSignalsXStop())[ch];

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