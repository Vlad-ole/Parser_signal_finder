#include "Single_pe_characteristics.h"
#include <iostream>
#include <vector>

//using namespace std;

//SinglePeCharacteristics::SinglePeCharacteristics()
//{
//
//}

std::vector<SinglePeCharacteristics> single_pe_characteristics;

SinglePeCharacteristics::SinglePeCharacteristics(int ch_id, bool is_physical, bool is_spe_separated_from_noise, double spe_mean, double spe_min, double spe_max) :
ch_id(ch_id), is_physical(is_physical), is_spe_separated_from_noise(is_spe_separated_from_noise), spe_mean(spe_mean), spe_min(spe_min), spe_max(spe_max)
{
}

void initialize_single_pe_characteristics()
{
	single_pe_characteristics.push_back(SinglePeCharacteristics(32, true, true, 1482, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(33, true, true, 1256, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(34, true, true, 1622, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(35, true, true, 1569, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(36, true, true, 1654, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(37, true, true, 1419, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(38, true, true, 1705, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(39, true, true, 1565, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(40, true, true, 1548, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(41, true, true, 1594, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(42, true, true, 1564, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(43, true, true, 1581, 750, 3000));

	single_pe_characteristics.push_back(SinglePeCharacteristics(44, true, false, 828, 0, 3000));

	single_pe_characteristics.push_back(SinglePeCharacteristics(48, true, true, 1540, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(49, true, true, 1210, 500, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(50, true, true, 1307, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(51, true, true, 1528, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(52, true, true, 1771, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(53, true, true, 1769, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(54, true, true, 1493, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(55, true, true, 1561.59, 750, 3000));

	single_pe_characteristics.push_back(SinglePeCharacteristics(56, true, false, 0, 750, 3000));

	single_pe_characteristics.push_back(SinglePeCharacteristics(57, true, true, 1592.03, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(58, true, true, 1535, 750, 3000));
	single_pe_characteristics.push_back(SinglePeCharacteristics(59, true, true, 1543, 750, 3000));

	std::cout << "inside void initialize_single_pe_characteristics()" << std::endl;
}

//c++ 11 may be, root cern gives error
//std::vector<SinglePeCharacteristics> single_pe_characteristics = 
//{
//	{ 32, true, true, 1482, 750, 3000 },
//	{ 33, true, true, 1256, 750, 3000 }
//};

