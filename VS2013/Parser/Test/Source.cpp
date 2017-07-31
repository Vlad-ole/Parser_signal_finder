#include <iostream>
#include "file1.h"

using namespace std;


int main()
{
	//do_something();
	//Helper helper;
	//helper.Initialize();
	//for (int i = 0; i < helper.struct_test_vec_obj.size(); i++)
	//{
	//	cout << "x = " << helper.struct_test_vec_obj[i].x << "; y = " << helper.struct_test_vec_obj[i].y << endl;
	//}

	std::vector<StructTest> struct_test_vec_obj = initialize();
	for (int i = 0; i < struct_test_vec_obj.size(); i++)
	{
		cout << "x = " << struct_test_vec_obj[i].x << "; y = " << struct_test_vec_obj[i].y << endl;
	}

	//system("pause");
	return 0;
}