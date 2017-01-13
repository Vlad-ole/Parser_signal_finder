#include "ReadData.h"
#include <sstream>

using namespace std;

#include <iomanip>

ReadData::ReadData(const string path_name, const int file_number, const std::vector<ch_info> ch_list, struct comm_info str_comm)
{
	data.resize(ch_list.size());
	data_double.resize(ch_list.size());
	const int vsize = 10000;
	vector<unsigned char> header(357);

	for (int i = 0; i < ch_list.size(); i++)
	{
		data[i].resize(vsize);
		data_double[i].resize(vsize);
		
		stringstream file_full_path;
		file_full_path << path_name << "C" << ch_list[i].id << "Trace" << setfill('0') << setw(5) << file_number << ".trc";

		cout << "file_full_path = " << file_full_path.str() << endl;
		//file.open(file_full_path.str());
		//I do not why, but c++ style of reading gives unexpected result, i.e. incorrect reading
		//so I chose usual c-style

		FILE *f = fopen(file_full_path.str().c_str(), "rb");

		if (/*!file.is_open()*/f == NULL)
		{
			cout << "can't open this file: " << file_full_path.str() << endl;
			system("pause");
			fclose(f);
			exit(1);
		}

		fread(&header[0], sizeof(vector<unsigned char>::value_type), header.size(), f);
		fread(&data[i][0], sizeof(vector<short int>::value_type), vsize, f);
		fclose(f);

		//y points to volts
		for (int j = 0; j < 10; j++)
		{
			data_double[i][j] = ch_list[i].VERTICAL_GAIN * data[i][j] - ch_list[i].VERTICAL_OFFSET;
			//cout << i << " " << j << " " << data[i][j] << " " <<  data_double[i][j] << endl;
		}


	}

}

ReadData::~ReadData()
{
}

std::vector<std::vector<double>> ReadData::GetDataDouble()
{
	return data_double;
}
