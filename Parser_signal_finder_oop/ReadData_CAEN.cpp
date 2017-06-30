#include "ReadData_CAEN.h"
#include <sstream>
#include <iomanip>

using namespace std;




ReadData_CAEN::ReadData_CAEN(path_info PathInfo, const std::vector<ch_info> ch_list, struct comm_info str_comm)
{
	data.resize(ch_list.size());
	data_double.resize(ch_list.size());
	const int vsize = 99990;

	time.resize(vsize);
	for (int i = 0; i < vsize; i++)
	{
		time[i] = i * str_comm.HORIZ_INTERVAL;
	}

	for (int i = 0; i < ch_list.size(); i++)
	{
		data[i].resize(vsize);
		data_double[i].resize(vsize);

		stringstream file_full_path;
		file_full_path << PathInfo.path_name << "run_" << PathInfo.event_number <<  "__ch_" << ch_list[i].id << ".dat";

		//cout << "file_full_path = " << file_full_path.str() << endl;
		//file.open(file_full_path.str());
		//I do not why, but c++ style of reading gives unexpected result, i.e. incorrect reading
		//so I chose usual c-style.
		//The problem in structures. I should use #pragma pack to write structures correctry to the disc.

		FILE *f = fopen(file_full_path.str().c_str(), "rb");

		if (/*!file.is_open()*/f == NULL)
		{
			cout << "can't open this file: " << file_full_path.str() << endl;
			system("pause");
			fclose(f);
			exit(1);
		}

		fread(&data[i][0], sizeof(vector<short int>::value_type), vsize, f);
		fclose(f);

		//y points to volts
		for (int j = 0; j < vsize; j++)
		{
			//data_double[i][j] = (ch_list[i].VERTICAL_GAIN * data[i][j] - ch_list[i].VERTICAL_OFFSET) * 1000/*V -> mV */;
			data_double[i][j] = ((2 / 4095.0) * data[i][j] - 1) * 1000;
			//cout << i << " " << j << " " << data[i][j] << " " <<  data_double[i][j] << endl;
		}


	}

}


ReadData_CAEN::~ReadData_CAEN()
{
}
