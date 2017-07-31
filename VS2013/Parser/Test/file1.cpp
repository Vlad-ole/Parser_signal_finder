#include "file1.h"

StructTest::StructTest(double x, double y) : x(x), y(y)
{
}

////std::vector<StructTest> struct_test_vec_obj;
//
//void do_something()
//{
//	for (int i = 0; i < 1; i++)
//	{
//		//struct_test_vec_obj.push_back( StructTest(i, i * 10) );
//	}	
//}

////
//Helper::Helper()
//{
//}
//
//Helper::~Helper()
//{
//}
//
//void Helper::Initialize()
//{	
//	for (int i = 0; i < 10; i++)
//	{
//		struct_test_vec_obj.push_back(StructTest(i, i * 10));
//	}
//}

std::vector<StructTest> initialize()
{
	std::vector<StructTest> struct_test_vec_obj;
	for (int i = 0; i < 10; i++)
	{
		struct_test_vec_obj.push_back(StructTest(i, i * 10));
	}
	return struct_test_vec_obj;
}