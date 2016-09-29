#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
	//vector<double> xv;
	//vector<unsigned char /*short int*/ > yv;
	//int vsize = 50000;
	//double time_scale = 20; //[ns / point]

	//string dir_name = "D://Data_work//run1_2_n//";
	//ostringstream f_oss;
	//f_oss << dir_name << "C1Trace" << setfill('0') << setw(5) <<  1 << ".trc"; //my PC
	//FILE *f = fopen(f_oss.str().c_str(), "rb");
	//if (f == NULL)
	//{
	//	cout << "Can't open this file: " << f_oss.str().c_str() << endl;
	//	system("pause");
	//	fclose(f);
	//	exit(1);
	//}

	//yv.resize(vsize);
	//fread(&yv[0], sizeof(vector</*short int*/ unsigned char>::value_type), vsize, f);

	//xv.resize(vsize);
	//for (int i = 0; i < vsize; i++)
	//{
	//	xv[i] = time_scale * i;
	//}

	//for (int i = 0; i < 200; i++)
	//{
	//	cout << xv[i] << "\t" << (double)yv[i] << endl;
	//}








	unsigned int type_of_file = 1;
	unsigned int number_of_file = 1;

	vector<double> xv_;

	vector<unsigned char> yv_one_byte;
	vector<unsigned short int> yv_two_byte;
	vector<double> yv_double;
	int vsize = 5000;
	double time_scale = 20 / 1000.0; //[us / point]


	string dir_name = "D://Data_work//test//";
	ostringstream f_oss;
	f_oss << dir_name << "C1Trace" << setfill('0') << setw(5) << number_of_file << ".trc"; //my PC
	FILE *f = fopen(f_oss.str().c_str(), "rb");
	if (f == NULL)
	{
		cout << "Can't open this file: " << f_oss.str().c_str() << endl;
		system("pause");
		exit(1);		
	}

	if (type_of_file == 1)
	{
		yv_one_byte.resize(vsize);
		fread(&yv_one_byte[0], sizeof(vector<unsigned char>::value_type), vsize, f);
	}
	if (type_of_file == 2)
	{
		yv_two_byte.resize(vsize);
		fread(&yv_two_byte[0], sizeof(vector<unsigned short int>::value_type), vsize, f);
	}


	xv_.resize(vsize);
	for (int i = 0; i < vsize; i++)
	{
		xv_[i] = time_scale * i;
	}

	yv_double.resize(vsize);
	for (int i = 0; i < vsize; i++)
	{
		if (type_of_file == 1)
			yv_double[i] = (double)yv_one_byte[i];

		if (type_of_file == 2)
			yv_double[i] = (double)yv_two_byte[i];
	}

	

	for (int i = 0; i < 200; i++)
	{
		cout << xv_[i] << "\t" << (int)yv_double[i] << endl;
	}
	
	cout << f_oss.str() << endl;

	system("pause");
	return 0;
}