#include "file1.h"

double a = 10;



//StructTest::StructTest()
//{
//}

StructTest::StructTest(double x, double y) : x(x), y(y)
{
}

StructTest struct_test_obj(11,22);

std::vector<StructTest> struct_test_vec_obj;

void do_something()
{
	struct_test_vec_obj.push_back(StructTest(12, 23));
}