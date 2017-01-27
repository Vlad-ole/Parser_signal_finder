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
	//TApplication theApp("theApp", &argc, argv);//let's add some magic! https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=22972
	//gROOT->SetBatch(kTRUE);


	const string path_name = "D:\\Data_work\\161026\\run7\\";
	string str_tree_common_info = path_name + "trees\\common_info.root";
	TFile f(str_tree_common_info.c_str());
	TTree *tree = (TTree*)f.Get("common_info");
	double HORIZ_INTERVAL;
	tree->SetBranchAddress("HORIZ_INTERVAL", &HORIZ_INTERVAL);
	tree->GetEntry(0);
	f.Close();
	cout << "HORIZ_INTERVAL = " << HORIZ_INTERVAL << endl;

	TObjArray Hlist_gr(0);
	Hlist_gr.SetOwner(kTRUE);

	//Chain chain;
	TChain chain("t1");
	string str_chain = path_name + "trees\\Block0000000.root";
	chain.Add(str_chain.c_str());

	double baseline_ch0, baseline_ch1;
	double min_ch0, min_ch1;
	double max_ch0, max_ch1;
	double n_peaks_caen;
	
	int point_s2_left_caen, point_s2_right_caen;
	vector<double> *time = 0;
	vector<double> *data_raw_ortec = 0;
	vector<double> *data_raw_caen = 0;
	vector<double> *data_smooth_caen = 0;
	vector<double> *data_der_ortec = 0;
	vector<double> *data_der_caen = 0;
	vector<double> *data_int_ortec = 0;
	vector<double> *data_int_caen = 0;
	vector<int> *peak_position_caen = 0;
	vector<double> *baseline_vec_caen = 0;
	double integral_s1_caen;
	double integral_s2_caen;

	chain.SetBranchAddress("baseline_ch0", &baseline_ch0);
	chain.SetBranchAddress("baseline_ch1", &baseline_ch1);
	chain.SetBranchAddress("baseline_vec_caen", &baseline_vec_caen);

	chain.SetBranchAddress("min_ch0", &min_ch0);
	chain.SetBranchAddress("min_ch1", &min_ch1);

	chain.SetBranchAddress("max_ch0", &max_ch0);
	chain.SetBranchAddress("max_ch1", &max_ch1);

	chain.SetBranchAddress("time", &time);

	chain.SetBranchAddress("data_raw_ortec", &data_raw_ortec);
	chain.SetBranchAddress("data_raw_caen", &data_raw_caen);

	chain.SetBranchAddress("data_der_ortec", &data_der_ortec);
	chain.SetBranchAddress("data_der_caen", &data_der_caen);

	chain.SetBranchAddress("data_smooth_caen", &data_smooth_caen);

	chain.SetBranchAddress("data_int_ortec", &data_int_ortec);
	chain.SetBranchAddress("data_int_caen", &data_int_caen);

	chain.SetBranchAddress("peak_position_caen", &peak_position_caen);
	chain.SetBranchAddress("n_peaks_caen", &n_peaks_caen);

	chain.SetBranchAddress("point_s2_left_caen", &point_s2_left_caen);
	chain.SetBranchAddress("point_s2_right_caen", &point_s2_right_caen);

	chain.SetBranchAddress("integral_s1_caen", &integral_s1_caen);
	chain.SetBranchAddress("integral_s2_caen", &integral_s2_caen);

	const int n_events = chain.GetEntries();
	int pass_counter = 0;
	//const int n_events = 10;
	cout << "chain.GetEntries() = " << chain.GetEntries() << endl;

	if (1)
	{
		gROOT->SetBatch(kFALSE);
		TCut cut1 = "min_ch1 > -1000 && max_ch1 < 4000";
		TCut cut_s2 = "n_peaks_caen > 15";
		chain.Draw("integral_s1_caen:integral_s2_caen", cut1 && cut_s2);
	}

	
	if (0)
	{
		for (int i = 0; i < n_events; i++)
		{
			chain.GetEntry(i);
			if (i % 10 == 0)
			{
				cout << "event = " << i << endl;
			}

			Data data;
			data.HORIZ_INTERVAL = HORIZ_INTERVAL;
			data.baseline_ch0 = baseline_ch0;
			data.baseline_ch1 = baseline_ch1;
			data.max_ch0 = max_ch0;
			data.max_ch1 = max_ch1;
			data.min_ch0 = min_ch0;
			data.min_ch1 = min_ch1;
			data.time = *time;
			data.data_raw_ortec = *data_raw_ortec;
			data.data_raw_caen = *data_raw_caen;
			data.data_der_ortec = *data_der_ortec;
			data.data_der_caen = *data_der_caen;
			data.data_int_ortec = *data_int_ortec;
			data.data_int_caen = *data_int_caen;
			data.peak_position_caen = *peak_position_caen;
			data.baseline_vec_caen = *baseline_vec_caen;
			data.data_smooth_caen = *data_smooth_caen;
			data.point_s2_left_caen = point_s2_left_caen;
			data.point_s2_right_caen = point_s2_right_caen;
			data.integral_s1_caen = integral_s1_caen;
			data.integral_s2_caen = integral_s2_caen;
			
			//cuts
			//bool cut1_caen_run3 = min_ch1 > -1000 && max_ch1 < 4500;
			//bool cut1_ortec_run3 = min_ch0 > -100 && max_ch1 < 700;

			//run7
			bool cut_s2_caen_run7 = n_peaks_caen > 15;
			bool cut1_caen_run7 = min_ch1 > -1000 && max_ch1 < 4000;

			if (cut1_caen_run7 && cut_s2_caen_run7)
			{
				pass_counter++;
				cout << "passed event: " << i << endl;
				FormCanv form_canv(data);
				//TPad* pad = (TPad*)(form_canv.GetCanv()).GetListOfPrimitives()->FindObject("c_2");
				//TGraph* gr = (TGraph*)pad->GetListOfPrimitives()->FindObject("Graph");

				//if (pad == NULL || gr == NULL)
				//{
				//	cout << "pad == NULL || gh == NULL" << endl;
				//	system("pause");
				//}

				//Hlist_gr.Add(gr->Clone());
				Hlist_gr.Add((form_canv.GetCanv()).Clone());
			}
		}

		//cout << "pass_counter = " << pass_counter << endl;
		//TCanvas* canv_write = new TCanvas("c", "c", 0, 0, 1900, 1000);
		//for (int i = 0; i < pass_counter; i++)
		//{
		//	TGraph* gr = (TGraph*)Hlist_gr.At(i);
		//	if (i == 0) gr->Draw();
		//	else gr->Draw("same");
		//}

		string str_ofile = path_name + "result.root";
		TFile ofile_Hlist_gr(str_ofile.c_str(), "RECREATE");
		Hlist_gr.Write();
		//canv_write->Write();
		ofile_Hlist_gr.Close();
	}
	
	cout << "all is ok" << endl;
	system("pause");
	//theApp.Terminate();
	//theApp.Run();
	return 0;
}