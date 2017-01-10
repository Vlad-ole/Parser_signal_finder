#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>

#include "TF1.h"
#include "TGraph.h"

#include "Baseline_calc.h"




using namespace std;



//calculate and set baseline
vector<double> calculate_and_set_baseline(vector<double> xv, vector<double> yv, vector< vector<double> > t_start_stop_V, const double time_scale, const unsigned int number_of_channel)
{
	vector<double> baselineV;
	vector<double> baselineV_single;
	vector<double> t_start_V = t_start_stop_V[0];
	vector<double> t_stop_V = t_start_stop_V[1];

	baselineV.resize(yv.size());
	double summ = 0;
	
	vector<TF1*> TF1V;
	vector<string> stringV;
	vector<double> par0V;



	TGraph gr0(yv.size(), &xv[0], &yv[0]);
	
	bool the_first = true;
	//calculate baseline
	clock_t t_before = clock();
	for (int i = 0; i < t_start_V.size(); i++)
	{
		////variant 1(CPU expensive)
		//stringstream ss;
		//ss << "f" << i;
		//string tf1_name = ss.str();
		//TF1 f(tf1_name.c_str(), "[0]", t_start_V[i], t_stop_V[i]);
		//cout << "tf1_name = " << tf1_name << endl;
	
		//if (the_first)
		//{
		//	gr0.Fit(tf1_name.c_str(), "R");
		//	the_first = false;
		//}
		//else
		//{
		//	gr0.Fit(tf1_name.c_str(), "R+");
		//}
		//baselineV_single.push_back(f.GetParameter(0));

		////variant 2(CPU cheap, no disadvantages)
		double avr = 0;
		int start = (int)(t_start_V[i] / time_scale);
		int stop = (int)(t_stop_V[i] / time_scale);
		for (int j = start; j < stop; j++)
		{
			avr += yv[j];
		}
		baselineV_single.push_back(avr / (stop - start) );
	
	}
	clock_t t_after = clock();
	t_calculate_baseline += t_after - t_before;


	//set baseline
	t_before = clock();
	t_start_V[0] = 0;
	for (int i = 0; i < t_start_V.size() - 1; i++)
	{
		for (int j = (int)(t_start_V[i] / time_scale); j < (int)(t_start_V[i + 1] / time_scale); j++)
		{
			baselineV[j] = baselineV_single[i];
		}
	}
	for (int i = (int)(t_start_V[t_start_V.size() - 1] / time_scale); i < yv.size(); i++)
	{
		baselineV[i] = baselineV_single[t_start_V.size() - 1];
	}
	t_after = clock();
	t_set_baseline += t_after - t_before;

	return baselineV;
}