#pragma once
#include "ReadData.h"

///read data from .trc files (LeCroy oscilloscope)
class ReadData_LeCroy :
	public ReadData
{
public:
	ReadData_LeCroy(const std::string path_name, const int file_number, const std::vector<ch_info> ch_list, struct comm_info str_comm);
	~ReadData_LeCroy();
};

