#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>


using namespace std;

struct WAVEDESC
{
	char DESCRIPTOR_NAME[27] = {"#9000040350WAVEDESC"};
	char TEMPLATE_NAME[16] = {"LECROY_2_3"};
	char COMM_TYPE[2] = {1};
	char COMM_ORDER[2] = {1};
	long int WAVE_DESCRIPTOR = 346;
} Wavedesc;

int main(int argc, char *argv[])
{
	fstream file;

	file.open("D://git_repositories//Parser_signal_finder//test_data.txt", ios::out | ios::binary);
	if (!file.is_open())
	{
		cout << "can't open this file: " << "D://git_repositories//Parser_signal_finder//test_data.txt" << endl;
		system("pause");
		file.close();
		exit(1);
	}

	file.write( (char*)& Wavedesc, sizeof(Wavedesc) );

	file.close();

	//	------------------------------
	file.open("D://git_repositories//Parser_signal_finder//test_data.txt", ios::in | ios::binary);
	if (!file.is_open())
	{
		cout << "can't open this file: " << "D://git_repositories//Parser_signal_finder//test_data.txt" << endl;
		system("pause");
		file.close();
		exit(1);
	}

	file.read((char*)& Wavedesc, sizeof(Wavedesc));

	cout << "Wavedesc.DESCRIPTOR_NAME = " << Wavedesc.DESCRIPTOR_NAME << endl;
	cout << "Wavedesc.TEMPLATE_NAME = " << Wavedesc.TEMPLATE_NAME << endl;
	cout << "Wavedesc.COMM_TYPE = " << (int) Wavedesc.COMM_TYPE[0] << endl;
	cout << "Wavedesc.COMM_ORDER = " << (int) Wavedesc.COMM_ORDER[0] << endl;
	cout << "Wavedesc.WAVE_DESCRIPTOR = " << Wavedesc.WAVE_DESCRIPTOR << endl;


	file.close();

	cout << "all is ok" << endl;
	system("pause");
	return 0;
}