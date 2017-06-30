#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

#include <stdlib.h>     /* srand, rand */

using namespace std;

int main(int argc, char *argv[])
{
	string path_name("D://Data_work//test_folder//");
	stringstream file_full_path;

	int run_number = 2721;
	int ch = 0;
	file_full_path << path_name << "run_" << run_number << "__ch_" << ch << ".dat";
	ofstream f(file_full_path.str().c_str(), ios::out | ios::binary);

	stringstream file_full_path_txt;
	file_full_path_txt << path_name << "run_" << run_number << "__ch_" << ch << ".txt";
	ofstream f_txt(file_full_path_txt.str().c_str());

	/* initialize random seed: */
	srand(time(NULL));
	
	vector<short int> num;
	const int n = 9999 * 10;
	num.resize(n);

	for (int i = 0; i < n; i++)
	{
		/* generate secret number between 0 and 4095: */
		num[i] = rand() % 4095;
		f_txt << num[i] << endl;
	}

	f.write((char*)&num[0], num.size() * sizeof(short int));
	

	return 0;
}