#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<double> a;
	a.resize(300000000);
	cout << a.size() << endl;
	
	system("pause");
	return 0;
}