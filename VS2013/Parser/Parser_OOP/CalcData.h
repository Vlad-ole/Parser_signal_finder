#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "CalcBaseline.h"
#include "CalcDer.h"
#include "PeakFinder.h"

#include "CoGBase.h"

class CalcData
{
public:
	CalcData(std::vector< std::vector<double> >& data, std::vector<double>& time, double HORIZ_INTERVAL);
	~CalcData();

	//CalcData& operator=(const CalcData& CD);

	std::vector< std::vector<double> >& GetData();
	std::vector< std::vector<double> >& GetDataMinBaseline();
	std::vector<double>& GetTime();

	std::vector<double>& GetBaseline();
	std::vector< std::vector<double> >& GetBaselineVec();
	std::vector< std::vector<double> >& GetDer();
	std::vector< std::vector<double> >& GetInt();
	std::vector< std::vector<double> >& GetSmooth();
	std::vector<double>& GetMax();
	std::vector<double>& GetMin();
	std::vector<int>& GetDerMaxPosition();
	std::vector<int>& GetDerMinPosition();

	std::vector< std::vector<int> >& GetPeakPosition();

	int GetPointS2Left();
	int GetPointS2Right();

	std::vector<double> GetIntegral();
	std::vector<double> GetIntegralS2();

	std::vector<double>& GetYvCut();

	double GetIntegral_s1_caen_outside_the_trigger();

	std::vector<double> GetInvertSignal(std::vector<double> yv, double baseline);

	std::vector< std::vector<double> >& GetIntegralOnePeak();
	std::vector<double>& GetIntegralOneEvent();
	std::vector< std::vector<double> >& GetLocalBaselineV();
	std::vector< std::vector<int> >& GetSignalsXStart();
	std::vector< std::vector<int> >& GetSignalsXStop();

	std::vector< std::vector<double> >& GetDoubleIntegralVec();
	std::vector< std::vector<double> >& GetDoubleIntegralVecY();

	std::vector<double>& GetNumOfPeInEventVec();

	double GetXCogPosition();
	double GetYCogPosition();

private:
	std::vector< std::vector<double> >& data;
	std::vector<double>& time;

	std::vector<double> max;
	std::vector<double> min;

	std::vector<int> der_min_position;
	std::vector<int> der_max_position;
	
	std::vector<double> baseline;
	std::vector< std::vector<double> > baseline_vec;
	std::vector< std::vector<double> > smooth_data;
	std::vector< std::vector<double> > der_data;
	std::vector< std::vector<double> > int_data;
	std::vector< std::vector<double> > data_min_baseline;

	std::vector< std::vector<int> > peak_position;

	std::vector< std::vector<double> > integral_s1_s2;

	std::vector< std::vector<double> > integral_one_peak;
	std::vector<double> integral_one_event;
	std::vector< std::vector<double> > local_baseline_v;
	std::vector< std::vector<int> > signals_x_start_v;
	std::vector< std::vector<int> > signals_x_stop_v;

	std::vector< std::vector<double> > double_integral_vec;
	std::vector< std::vector<double> > double_integral_vec_y;

	int point_s2_left;
	int point_s2_right;

	std::vector<double> integral;
	std::vector<double> integral_s2;

	double integral_s1_caen_outside_the_trigger;

	std::vector<double> yv_cut;
	std::vector<double> num_of_pe_in_event_vec;

	double x_cog_position;
	double y_cog_position;
};

