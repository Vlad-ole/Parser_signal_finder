#include "file1.h"

//correct
double a = 10;

StructTest::StructTest(double x, double y) : x(x), y(y)
{
}
StructTest struct_test_obj(11,22);

std::vector<StructTest> struct_test_vec_obj;

void do_something()
{
	for (int i = 0; i < 100; i++)
	{
		struct_test_vec_obj.push_back( StructTest(i, i * 10) );
	}	
}


////test
//std::vector<SinglePeCharacteristics> single_pe_characteristics;
//
////SinglePeCharacteristics::SinglePeCharacteristics()
////{
////}
//
//SinglePeCharacteristics::SinglePeCharacteristics(int ch_id, bool is_physical, bool is_spe_separated_from_noise, double spe_mean, double spe_min, double spe_max) :
//ch_id(ch_id), is_physical(is_physical), is_spe_separated_from_noise(is_spe_separated_from_noise), spe_mean(spe_mean), spe_min(spe_min), spe_max(spe_max)
//{
//}
//
//void initialize_single_pe_characteristics()
//{
//	for (int i = 0; i < 100; i++)
//	{
//		single_pe_characteristics.push_back(SinglePeCharacteristics(32, true, true, 1482, 750, 3000));
//	}
//	
//	std::cout << "inside void initialize_single_pe_characteristics()" << std::endl;
//}


