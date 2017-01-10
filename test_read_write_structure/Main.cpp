#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>


using namespace std;

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

	int x = 50;
	//char str[] = {'a', 'b', 'c', '\0'};
	char str[] = "abc";

	file.write( (char*)& x, sizeof(x) );
	file.write( (char*)& str, sizeof(str) );

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

	int y;
	char buf[4];

	file.read((char*)& y, sizeof(y));
	file.read((char*)& buf, sizeof(buf));

	cout << "y = " << y << endl;
	cout << "buf = " << buf << endl;

	file.close();

	cout << "all is ok" << endl;
	system("pause");
	return 0;
}