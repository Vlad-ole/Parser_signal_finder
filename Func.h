#pragma ones

#include <vector>

using namespace std;

double fit_exp(double *x, double *par);
vector<double> integral_vs_time(vector<double> yv, vector<double> baseline, double time_scale);
vector< vector<double> > find_start_and_stop(vector<double> yv_der, double th, double time_scale, double dead_time);
vector<double> find_s1_area(vector<double> xv, vector<double> yv, vector< vector<double> > t_start_stop_V);
double find_s2_area(vector<double> yv_integral, double time_scale);