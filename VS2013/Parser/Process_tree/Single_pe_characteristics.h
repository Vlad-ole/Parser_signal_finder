#ifndef _Single_pe_characteristics
#define _Single_pe_characteristics


//#include <iostream>
//#include <vector>

//using namespace std;
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
	//SinglePeCharacteristics();
};

extern std::vector<SinglePeCharacteristics> single_pe_characteristics;

void initialize_single_pe_characteristics();

#endif //_Single_pe_characteristics
