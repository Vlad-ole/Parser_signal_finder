#ifndef _file1
#define _file1

#include <iostream>
#include <vector>

extern double a;
void do_something();

struct StructTest
{
	double x;
	double y;
	//StructTest();
	StructTest(double x, double y);
};

extern StructTest struct_test_obj;
extern std::vector<StructTest> struct_test_vec_obj;

#endif // _file1