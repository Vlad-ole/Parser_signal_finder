#pragma once

#include <iostream>
#include <vector>
#include <fstream>

struct ch_info
{
	int id;	
	double VERTICAL_OFFSET;
	double VERTICAL_GAIN;
};

struct comm_info
{
	int write_type;
	double HORIZ_INTERVAL;
	double time_offset;
};

///read data from .trc files (LeCroy oscilloscope)
class ReadData
{
public:
	ReadData(const std::string path_name, const int file_number, const std::vector<ch_info> ch_list, struct comm_info str_comm);
	~ReadData();
	std::vector< std::vector<double> > GetDataDouble();
	std::vector<double> GetTimeArray();
private:
	std::vector< std::vector<short int> > data;
	std::vector< std::vector<double> > data_double;
	std::vector<double> time;
};

