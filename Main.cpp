#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

#include "TF1.h"
#include "TGraph.h"

#include "Func.h"
#include "Golay_filter.h"
#include "Input_Output.h"
#include "Baseline_calc.h"

using namespace std;

double t_calculate_baseline = 0;
double t_set_baseline = 0;

int main(int argc, char *argv[])
{
	vector<double> xv;

	const int vsize = 50000;
	const double time_scale = 2; //[ns / point]	
	const bool show_graphs = false;
	const string dir_name = "D://Data_work//run_2_bkg//";


	//x points to ns
	xv.resize(vsize);
	for (int i = 0; i < vsize; i++)
	{
		xv[i] = time_scale * i;
	}

	ofstream file_out("D://Data_work//bkg_results_short.dat");

	int n_start = 0;
	int n_of_files = 9901;
	clock_t t_0 = clock();

	clock_t t_read_file = 0;
	clock_t t_CalculateDerivative = 0;
	clock_t t_find_start_and_stop = 0;
	clock_t t_calculate_and_set_baseline = 0;
	clock_t t_integral_vs_time = 0;
	clock_t t_find_s1_area = 0;
	clock_t t_find_s2_area = 0;

	for (int number_of_file = n_start; number_of_file < n_start + n_of_files; number_of_file++)
	{
		//read file
		clock_t t_before = clock();
		vector<double> yv;
		yv = read_file(dir_name, number_of_file, 1, vsize);
		clock_t t_after = clock();
		t_read_file += t_after - t_before;

		//calculate derivative (Savitzky–Golay filter)
		t_before = clock();
		const int points = 101; //this number must be odd!!! 101 points -> 202 ns ~ tau of PMT signal
		vector<double> yv_der = CalculateDerivative(yv, points);
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
		vector<double> baselineV = calculate_and_set_baseline(xv, yv, t_start_stop_V, time_scale);
		t_after = clock();
		t_calculate_and_set_baseline+= t_after - t_before;

		//integral_vs_time
		t_before = clock();
		vector<double> yv_integral = integral_vs_time(yv, baselineV, time_scale);//[V * ns]
		t_after = clock();
		t_integral_vs_time+= t_after - t_before;

		//find s1 & s2 area
		t_before = clock();
		double s1_area = find_s1_area(xv, yv, t_start_stop_V);
		t_after = clock();
		t_find_s1_area+= t_after - t_before;

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

	file_out.close();
	system("pause");
	return 0;
}






