#include <iostream>
#include <vector>
#include <sstream>

#include "TF1.h"
#include "TGraph.h"

#include "Func.h"

using namespace std;

double fit_exp(double *x, double *par)
{
	double time = x[0] - par[2];
	double fitval;
	if (time > 0)
	{
		fitval = par[0] + par[1] * exp(-time / par[3]);
	}
	else
	{
		fitval = par[0];
	}

	return fitval;
}


//integral of signal
vector<double> integral_vs_time(vector<double> yv, vector<double> baseline, double time_scale)
{
	vector<double> yv_result;
	yv_result.resize(yv.size());
	double summ = 0;

	for (int i = 0; i < yv.size(); i++)
	{
		summ += (yv[i] - baseline[i]);
		yv_result[i] = summ * time_scale;
	}

	return yv_result;
}



//find start and stop for future fitting
vector< vector<double> > find_start_and_stop(vector<double> yv_der, double th, double time_scale, double dead_time)
{
	vector<double> t_start_V;
	vector<double> t_stop_V;

	t_start_V.push_back(1000); // range 0 - 1000 ns is noisy 
	double time_max = 60000; //ns
	double time_trigg = 0;//???
	bool flag = true;
	double shift = 0;//ns

	int point_max = (int)(time_max / time_scale);
	for (int i = 0; i < point_max; i++)
	{
		if (yv_der[i] > th && flag)
		{
			t_stop_V.push_back(time_scale * i - shift); //[ns]
			flag = false;
			time_trigg = time_scale * i;
		}

		if (i * time_scale > (time_trigg + dead_time) && !flag)
		{
			flag = true;
			t_start_V.push_back(time_scale * i - shift);
		}

		if (yv_der[i] < th && flag && (i == point_max - 1))
		{
			t_stop_V.push_back(time_scale * i);
		}

	}

	vector< vector<double> > result_v;
	result_v.push_back(t_start_V);
	result_v.push_back(t_stop_V);
	return result_v;
}



vector<double> find_s1_area(vector<double> xv, vector<double> yv, vector< vector<double> > t_start_stop_V)
{
	vector<double> t_start_V = t_start_stop_V[0];
	vector<double> t_stop_V = t_start_stop_V[1];

	vector<double> result;
	result.resize(4);

	//cout << t_start_V.size() << "\t" << t_stop_V.size() << endl;
	
	//fit S1 signal
	if (t_stop_V[0] < 59000)
	{
		TGraph gr0(yv.size(), &xv[0], &yv[0]);
		TF1 fitFcn("fitFcn", fit_exp, t_stop_V[0], t_start_V[1], 4);

		fitFcn.SetLineColor(3);

		fitFcn.SetParLimits(0, -2.92442, -2.92442);
		fitFcn.SetParLimits(1, 0, 10);
		fitFcn.SetParLimits(2, t_stop_V[0], t_start_V[1]);
		fitFcn.SetParLimits(3, 150, 200);//ns 		


		fitFcn.SetParameter(0, -2.92442);
		fitFcn.SetParameter(1, 0.5);
		fitFcn.SetParameter(2, t_stop_V[0]);
		fitFcn.SetParameter(3, 100);
		//gr0.Fit("fitFcn", "R+");
		gr0.Fit("fitFcn", "RQ");

		result[0] = fitFcn.GetParameter(0);
		result[1] = fitFcn.GetParameter(1);
		result[2] = fitFcn.GetParameter(2);
		result[3] = fitFcn.GetParameter(3);
		//return fitFcn.GetParameter(1) * fitFcn.GetParameter(3);
	}

	return result;
}


double find_s2_area(vector<double> yv_integral, double time_scale)
{
	//rough estimate of S2 
	double integral_max = 0;
	for (int i = (int)(60000 / time_scale); i < (int)(100000 / time_scale); i++)
	{
		if (yv_integral[i] > integral_max)
			integral_max = yv_integral[i];
	}

	return integral_max;
}
