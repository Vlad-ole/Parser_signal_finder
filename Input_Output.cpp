#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

#include "Input_Output.h"

using namespace std;

vector<double> read_file(const string dir_name, const unsigned int file_number, const unsigned short int type_of_binary, const int vsize, const double voltage_scale, const int number_of_channel, const double approx_baseline)
{
	vector<double> yv;

	vector<unsigned char> yv_one_byte;
	vector<unsigned short int> yv_two_byte;

	ostringstream f_oss;
	f_oss << dir_name << "C" << number_of_channel << "Trace" << setfill('0') << setw(5) << file_number << ".trc"; //my PC
	FILE *f = fopen(f_oss.str().c_str(), "rb");
	if (f == NULL)
	{
		cout << "Can't open this file: " << f_oss.str().c_str() << endl;
		system("pause");
		fclose(f);
		exit(1);
	}
	else
	{
		cout << f_oss.str() << endl;
	}

	if (type_of_binary == 1)
	{
		yv_one_byte.resize(vsize);
		fread(&yv_one_byte[0], sizeof(vector<unsigned char>::value_type), vsize, f);
	}
	if (type_of_binary == 2)
	{
		yv_two_byte.resize(vsize);
		fread(&yv_two_byte[0], sizeof(vector<unsigned short int>::value_type), vsize, f);
	}

	fclose(f);


	//y points to volts
	yv.resize(vsize);
	for (int i = 0; i < vsize; i++)
	{
		if (type_of_binary == 1)
			yv[i] = (double)yv_one_byte[i];

		int real_value;
		if (type_of_binary == 2)
		{
			real_value = yv_two_byte[i] >> 4;
			yv[i] = (double)real_value;
		}

		double V_max = voltage_scale * 4;
		double k = V_max / 127.0;
		double b = -V_max * (1 + 128.0 / 127);
		//convert ADC code to Voltage
		if (yv[i] >= 0 && yv[i] <= 127)
			yv[i] *= k;
		else if (yv[i] >= 128 && yv[i] <= 255)
			yv[i] = k * yv[i] + b;
		else
			cout << "error in convert ADC code to Voltage" << endl;

	}

	//There strange noise in the start of the signal.
	//For right double integration we have to rewrite this noise to baseline value   
	for (int i = 0; i < 357; i++)
	{
		yv[i] = approx_baseline;
	}

	return yv;
}