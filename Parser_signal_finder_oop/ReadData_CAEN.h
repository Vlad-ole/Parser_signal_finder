#pragma once
#include "ReadData.h"
class ReadData_CAEN :
	public ReadData
{
public:
	ReadData_CAEN(const std::string path_name, const int file_number, const std::vector<ch_info> ch_list, struct comm_info str_comm);
	~ReadData_CAEN();
};

