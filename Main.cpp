#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

#include "TF1.h"
#include "TGraph.h"
#include "TFile.h"

#include "TRandom.h"
#include "TMath.h"
#include "TObjArray.h"
#include "TGraphErrors.h"
#include  "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"

#include "Func.h"
#include "Golay_filter.h"
#include "Input_Output.h"
#include "Baseline_calc.h"

#define write_trees

using namespace std;

double t_calculate_baseline = 0;
double t_set_baseline = 0;



int main(int argc, char *argv[])
{
	vector<double> xv;

	const int vsize = 20000;
	const double time_scale = 5; //[ns / point]	
	const double voltage_scale_c1 = 0.5; //[V / div]
	const double voltage_scale_c3 = 0.2; //[V / div]
	const bool show_graphs = false;
	const string dir_name = "D://Data_work//161005//run_1_n//";


	//x points to ns
	xv.resize(vsize);
	for (int i = 0; i < vsize; i++)
	{
		xv[i] = time_scale * i;
	}

	ofstream file_out("D://Data_work//161005//n_results_short.dat");
	ofstream file_out_details("D://Data_work//161005//n_results_in_detail.dat");

	const int n_start = 0;
	const int n_of_files = 1;
	clock_t t_0 = clock();

	clock_t t_read_file = 0;
	clock_t t_CalculateDerivative = 0;
	clock_t t_find_start_and_stop = 0;
	clock_t t_calculate_and_set_baseline = 0;
	clock_t t_integral_vs_time = 0;
	clock_t t_find_s1_area = 0;
	clock_t t_find_s2_area = 0;
	clock_t t_trees = 0;

	for (int number_of_file = n_start; number_of_file < n_start + n_of_files; number_of_file++)
	{
		//read file
		clock_t t_before = clock();
		vector<double> yv_c1;
		vector<double> yv_c3;
		yv_c1 = read_file(dir_name, number_of_file, 1, vsize, voltage_scale_c1, 1);// signal from ortec CSA
		yv_c3 = read_file(dir_name, number_of_file, 1, vsize, voltage_scale_c3, 3);// signal from cean CSA
		clock_t t_after = clock();
		t_read_file += t_after - t_before;

		//create root tree
#ifdef write_trees
			t_before = clock();
			string dir_trees = dir_name + "trees//";
			ostringstream file_tree_oss;
			file_tree_oss << dir_trees << "run_" << setfill('0') << setw(5) << number_of_file << ".root";
			TFile f_tree(file_tree_oss.str().c_str(), "RECREATE");
			TTree tree("t1", "Parser tree");
			
			TCanvas canv("c", "c", 0, 0, 1900, 1000);
			//canv.Divide(2, 2);
			//canv.cd(1);
			//graph_11.Draw();
			tree.Branch("canvas_tr", "TCanvas", &canv);

			TGraph graph_11(yv_c1.size(), &xv[0], &yv_c1[0]);			
			tree.Branch("gr_tr", "TGraph", &graph_11, 128000, 0);

			double baseline_par_br, amp_par_br, start_time_par_br, tau_par_br;//fit params
			double s2_area_br;

			tree.Branch("baseline_par_br", &baseline_par_br, "baseline_par_br/D");
			tree.Branch("amp_par_br", &amp_par_br, "amp_par_br/D");
			tree.Branch("start_time_par_br", &start_time_par_br, "start_time_par_br/D");
			tree.Branch("tau_par_br", &tau_par_br, "tau_par_br/D");
			tree.Branch("s2_area_br", &s2_area_br, "s2_area_br/D");
			t_after = clock();
			t_trees+= t_after - t_before;
#endif // write_trees


		//calculate derivative (Savitzky–Golay filter)
		t_before = clock();
		const int points = 101; //this number must be odd!!! 101 points -> 202 ns ~ tau of PMT signal
		vector<double> yv_der = CalculateDerivative(yv_c3, points);
		t_after = clock();
		t_CalculateDerivative+= t_after - t_before;

		//find start and stop
		t_before = clock();
		vector< vector<double> > t_start_stop_V;
		double th = 3E-3; // threshold for derivative [V / ns]
		double dead_time = 1000; //[ns]
		t_start_stop_V = find_start_and_stop(yv_der, th, time_scale, dead_time);
		t_after = clock();
		t_find_start_and_stop+= t_after - t_before;

		//calculate and set baseline
		t_before = clock();
		vector<double> baselineV = calculate_and_set_baseline(xv, yv_c1, t_start_stop_V, time_scale);
		t_after = clock();
		t_calculate_and_set_baseline+= t_after - t_before;

		//integral_vs_time
		t_before = clock();
		vector<double> yv_integral = integral_vs_time(yv_c1, baselineV, time_scale);//[V * ns]
		t_after = clock();
		t_integral_vs_time+= t_after - t_before;

		//find s1 & s2 area
		t_before = clock();
		vector<double> s1_fit_param = find_s1_area(xv, yv_c3, t_start_stop_V);
		double s1_area = s1_fit_param[1] * s1_fit_param[3];
		t_after = clock();
		t_find_s1_area+= t_after - t_before;

		//graph_11 = *(gr0);
		//gr0->GetMaximum();
		if (t_start_stop_V[0].size() > 1)
		{
			//cout << gr0 << endl;
			graph_11 = *(gr0);
		}
		

		t_before = clock();
		double s2_area = find_s2_area(yv_integral, time_scale);
		t_after = clock();
		t_find_s2_area += t_after - t_before;

		//view control
		
		//t_start, t_stop
		//cout << "t_start, t_stop" << endl;
		//for (int i = 0; i < t_start_stop_V[0].size(); i++)
		//{
		//	cout << t_start_stop_V[0][i] << "\t" << t_start_stop_V[1][i] << endl;
		//}

		//s1, s2 areas
		//cout << "s1 = " << s1_area << "\t s2 = " << s2_area << endl;
		file_out << s1_area << "\t" << s2_area << endl;
		file_out_details << s1_fit_param[0] << "\t" << s1_fit_param[1] << "\t" << s1_fit_param[2] << "\t" << s1_fit_param[3] << "\t" << s2_area << endl;

#ifdef write_trees
		t_before = clock();

		baseline_par_br = s1_fit_param[0];
		amp_par_br = s1_fit_param[1];
		start_time_par_br = s1_fit_param[2];
		tau_par_br = s1_fit_param[3];
		s2_area_br = s2_area;

		tree.Fill();
		tree.Write();

		t_after = clock();
		t_trees += t_after - t_before;
#endif // write_trees

	}

	cout << endl << "time of execition = " << (double)(clock() - t_0) / CLOCKS_PER_SEC << "\t (sec / file)[ms] = " << ( (double)(clock() - t_0) / CLOCKS_PER_SEC ) / n_of_files * 1000 << endl;
	cout << "t_read_file[ms] = " << (double)(t_read_file) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "t_CalculateDerivative[ms] = " << (double)(t_CalculateDerivative) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "t_calculate_and_set_baseline[ms] = " << (double)(t_calculate_and_set_baseline) / CLOCKS_PER_SEC * 1000 << endl;
		cout << "\t t_calculate_baseline[ms] = " << (double)(t_calculate_baseline) / CLOCKS_PER_SEC * 1000 << endl;
		cout << "\t t_set_baseline[ms] = " << (double)(t_set_baseline) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "t_integral_vs_time[ms] = " << (double)(t_integral_vs_time) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "t_find_s1_area[ms] = " << (double)(t_find_s1_area) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "t_find_s2_area[ms] = " << (double)(t_find_s2_area) / CLOCKS_PER_SEC * 1000 << endl;
	cout << "t_trees[ms] = " << (double)(t_trees) / CLOCKS_PER_SEC * 1000 << endl;

	file_out.close();
	system("pause");
	return 0;
}






