#include <iostream>
#include <vector>

using namespace std;
//#include <tuple> in c++11
//std::tuple<int, double> single_pe_characteristics;

struct SinglePeCharacteristics
{
	int ch_id;
	bool is_physical;
	bool is_spe_separated_from_noise;
	double spe_mean;
	double spe_min;
	double spe_max;
	SinglePeCharacteristics(int ch_id, bool is_physical, bool is_spe_separated_from_noise, double spe_mean, double spe_min, double spe_max);
	SinglePeCharacteristics();
};

SinglePeCharacteristics::SinglePeCharacteristics()
{
	
}

SinglePeCharacteristics::SinglePeCharacteristics(int ch_id, bool is_physical, bool is_spe_separated_from_noise, double spe_mean, double spe_min, double spe_max) :
ch_id(ch_id), is_physical(is_physical), is_spe_separated_from_noise(is_spe_separated_from_noise), spe_mean(spe_mean), spe_min(spe_min), spe_max(spe_max)
{
}

std::vector <SinglePeCharacteristics> single_pe_characteristics;

void initialize_single_pe_characteristics()
{
	single_pe_characteristics.push_back(SinglePeCharacteristics(32, true, true, 1482, 750, 3000));
}

//std::vector<double> test_vec;
//test_vec.pushback(1);
//test_vec.pushback(2);

//std::vector<SinglePeCharacteristics> single_pe_characteristics = 
//{
//	{ 32, true, true, 1482, 750, 3000 },
//	{ 33, true, true, 1256, 750, 3000 }
//};

