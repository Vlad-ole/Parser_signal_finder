#ifndef _file1
#define _file1

#include <iostream>
#include <vector>

//void do_something();

struct StructTest
{
	double x;
	double y;
	StructTest(double x, double y);
};

//extern std::vector<StructTest> struct_test_vec_obj;

//class Helper
//{
//public:
//	Helper();
//	~Helper();
//	void Initialize();
////private:
//	std::vector<StructTest> struct_test_vec_obj;
//};

std::vector<StructTest> initialize();




#endif // _file1