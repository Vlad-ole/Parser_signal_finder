#pragma once

#include <iostream>
#include <vector>
#include <fstream>

///read data from .trc files (LeCroy oscilloscope)
class ReadData
{
public:
	ReadData(const std::string path_name, const int file_number, const std::vector<int> ch_list);
	~ReadData();
private:
	std::vector< std::vector<double> > data;
	std::ifstream file;
	struct WAVEDESC
	{
		char DESCRIPTOR_NAME[20];
		char TEMPLATE_NAME[16];
		unsigned short int COMM_TYPE;
		unsigned short int COMM_ORDER;
		long int WAVE_DESCRIPTOR;
		long int USER_TEXT;
		long int RES_DESC1;

	} Wavedesc;
};

