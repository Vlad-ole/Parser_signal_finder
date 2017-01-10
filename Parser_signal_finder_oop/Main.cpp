#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

#include "ReadData.h"

using namespace std;

int main(int argc, char *argv[])
{
	const string path_name = "D:\\Data_work\\161026\\run3\\";
	const vector<int> ch_list{1};

	for (int event_number = 1; event_number <= 1; event_number++)
	{
		ReadData rdt(path_name, event_number, ch_list);
	}
	
	
	cout << "all is ok" << endl;
	system("pause");
	return 0;
}