#include "ChCharacteristics.h"

using namespace std;

double ChCharacteristics::step_x = 10; //mm
double ChCharacteristics::step_y = 10; //mm

ChCharacteristics::ChCharacteristics()
{
	ch_characteristics_struct = 
	{
		{ 32, true, true, 1482, 750, 3000, -2 * step_x, step_y },
		{ 33, true, true, 1256, 750, 3000, -step_x, 2 * step_y },
		{ 34, true, true, 1622, 750, 3000, 2 * step_x, 2 * step_y },
		{ 35, true, true, 1569, 750, 3000, -2 * step_x, step_y },
		{ 36, true, true, 1654, 750, 3000, step_x, step_y },
		{ 37, true, true, 1419, 750, 3000, 2 * step_x, step_y },
		{ 38, true, true, 1705, 750, 3000, 0, 0 },
		{ 39, true, true, 1565, 750, 3000, step_x, 0 },
		{ 40, true, true, 1548, 750, 3000, -step_x, -step_y },
		{ 41, true, true, 1594, 750, 3000, 0, -step_y },
		{ 42, true, true, 1564, 750, 3000, -2 * step_x, -2 * step_y },
		{ 43, true, true, 1581, 750, 3000, -step_x, -2 * step_y },
		{ 44, true, false, 828, 0, 3000, 2 * step_x, -2 * step_y },
		{ 48, true, true, 1540, 750, 3000, 0, 2 * step_y },
		{ 49, true, true, 1210, 500, 3000, step_x, 2 * step_y },
		{ 50, true, true, 1307, 750, 3000, -step_x, step_y },
		{ 51, true, true, 1528, 750, 3000, 0, step_y },
		{ 52, true, true, 1771, 750, 3000, -2 * step_x, 0 },
		{ 53, true, true, 1769, 750, 3000, -step_x, 0 },
		{ 54, true, true, 1493, 750, 3000, 2 * step_x, 0 },
		{ 55, true, true, 1561.59, 750, 3000, -2 * step_x, -step_y },
		{ 56, true, false, 0, 750, 3000, step_x, -step_y },
		{ 57, true, true, 1592.03, 750, 3000, 2 * step_x, -step_y },
		{ 58, true, true, 1535, 750, 3000, 0, -2 * step_y },
		{ 59, true, true, 1543, 750, 3000, step_x, -2 * step_y }

	};
}

ChCharacteristics::~ChCharacteristics()
{
}

vector<ChCharacteristicsStruct> ChCharacteristics::GetChCharacteristics()
{
	return ch_characteristics_struct;
}
