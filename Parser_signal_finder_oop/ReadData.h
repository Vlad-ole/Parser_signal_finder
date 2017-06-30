#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

struct path_info
{
	std::string path_name;
	int event_number;
};


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


class ReadData
{
public:
	ReadData();
	virtual ~ReadData() = 0;
	virtual std::vector< std::vector<double> >& GetDataDouble();
	virtual std::vector<double>& GetTimeArray();
protected:
	std::vector< std::vector<short int> > data;
	std::vector< std::vector<double> > data_double;
	std::vector<double> time;
};

