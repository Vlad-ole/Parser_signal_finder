#ifndef _file1
#define _file1

#include <iostream>
#include <vector>



//correct
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


////test
//void initialize_single_pe_characteristics();
//
//struct SinglePeCharacteristics
//{
//	int ch_id;
//	bool is_physical;
//	bool is_spe_separated_from_noise;
//	double spe_mean;
//	double spe_min;
//	double spe_max;
//	//SinglePeCharacteristics();
//	SinglePeCharacteristics(int ch_id, bool is_physical, bool is_spe_separated_from_noise, double spe_mean, double spe_min, double spe_max);
//};
//
//extern std::vector<SinglePeCharacteristics> single_pe_characteristics;


#endif // _file1