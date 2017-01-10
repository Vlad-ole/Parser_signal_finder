#pragma ones

#include <vector>

using namespace std;

extern double t_calculate_baseline;
extern double t_set_baseline;

vector<double> calculate_and_set_baseline(vector<double> xv, vector<double> yv, vector< vector<double> > t_start_stop_V, const double time_scale, const unsigned int number_of_channel);