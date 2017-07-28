#include <iostream>
#include "file1.h"

using namespace std;


int main()
{
	cout << "a = " << a << endl;
	do_something();

	cout << "struct_test_obj.x = " << struct_test_obj.x << endl;
	cout << "struct_test_obj.y = " << struct_test_obj.y << endl;

	cout << "struct_test_vec_obj.size() = " << struct_test_vec_obj.size() << endl;
	cout << "struct_test_vec_obj[0].x = " << struct_test_vec_obj[0].x << endl;
	cout << "struct_test_vec_obj[0].y = " << struct_test_vec_obj[0].y << endl;
	
	system("pause");
	return 0;
}