#include "CoGBase.h"
#include "ChCharacteristics.h"
#include "RunDescription.h"
//#include <tuple>

using namespace std;

CoGBase::CoGBase(std::vector<double> num_of_pe_in_event_vec)
{
	//var1: central row, central column
	x = 0;
	y = 0;
	double n_pe_x = 0;
	double n_pe_y = 0;

	//it is not ideal code, but right now I do not know how to make it better
	
	
	for (int i = 0; i < num_of_pe_in_event_vec.size(); i++)
	{
		int ch = GetChId(i);

		//for y
		if (ch == 48 || ch == 51 || ch == 38|| ch == 41|| ch == 58)
		{
			for (int j = 0; j < ChCharacteristics::GetChCharacteristics().size(); j++)
			{
				if (ChCharacteristics::GetChCharacteristics()[j].ch_id == ch)
				{
					y += num_of_pe_in_event_vec[i] * ChCharacteristics::GetChCharacteristics()[j].y_position;
					n_pe_y += num_of_pe_in_event_vec[i];
					break;
				}
			}			
		}

		//for x
		if ( ch == 52 || ch == 53 || ch == 38 || ch == 39 || ch == 54 )
		{
			for (int j = 0; j < ChCharacteristics::GetChCharacteristics().size(); j++)
			{
				if (ChCharacteristics::GetChCharacteristics()[j].ch_id == ch)
				{
					x += num_of_pe_in_event_vec[i] * ChCharacteristics::GetChCharacteristics()[j].x_position;
					n_pe_x += num_of_pe_in_event_vec[i];
					break;
				}
			}
		}

	}



	if (n_pe_y == 0 || n_pe_x == 0)
	{
		cout << "n_pe_y == 0 || n_pe_x == 0" << endl;
		//system("pause");
		//exit(1);
	}
	else
	{
		y /= n_pe_y;
		x /= n_pe_x;
	}
	
	
}

CoGBase::~CoGBase()
{
}

double CoGBase::GetX()
{
	return x;
}

double CoGBase::GetY()
{
	return y;
}