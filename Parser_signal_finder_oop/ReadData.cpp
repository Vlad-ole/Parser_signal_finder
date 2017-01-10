#include "ReadData.h"
#include <sstream>

using namespace std;

#include <iomanip>

ReadData::ReadData(const string path_name, const int file_number, const std::vector<int> ch_list)
{
	for (int i = 0; i < ch_list.size(); i++)
	{
		stringstream file_full_path;
		file_full_path << path_name << "C" << ch_list[i] << "Trace" << setfill('0') << setw(5) << file_number << ".trc";

		cout << "file_full_path = " << file_full_path.str() << endl;
		file.open(file_full_path.str());

		if (!file.is_open())
		{
			cout << "can't open this file: " << file_full_path.str() << endl;
			system("pause");
			file.close();
			exit(1);
		}

		//fread(&yv_one_byte[0], sizeof(vector<unsigned char>::value_type), vsize, f); // c style
		
		//var1
		//char ch;
		//for (int i = 0; i < 50; i++)
		//{
		//	file.read(&ch, sizeof(ch));
		//	cout << i << " " << ch << endl;
		//}

		//var2
		//char buffer[1];
		//file.read( (char*)(&buffer[0]), sizeof(buffer) );
		//cout << (int)buffer << endl;

		
		cout << endl;
		//file.read((char *)&Wavedesc, sizeof(Wavedesc));

		//cout << "Wavedesc.DESCRIPTOR_NAME = " << Wavedesc.DESCRIPTOR_NAME << endl;
		//cout << "Wavedesc.TEMPLATE_NAME = " << Wavedesc.TEMPLATE_NAME << endl;
		//cout << "Wavedesc.COMM_TYPE = " << Wavedesc.COMM_TYPE << endl;
		//cout << "Wavedesc.COMM_ORDER = " << Wavedesc.COMM_ORDER << endl;

		//cout << "Wavedesc.WAVE_DESCRIPTOR = " << Wavedesc.WAVE_DESCRIPTOR << endl;
		//cout << "Wavedesc.USER_TEXT = " << Wavedesc.USER_TEXT << endl;
		//cout << "Wavedesc.RES_DESC1 = " << Wavedesc.RES_DESC1 << endl;

		file.close();

	}

}

ReadData::~ReadData()
{
}
