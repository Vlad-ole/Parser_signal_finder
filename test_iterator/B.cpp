#include "B.h"



B::B(int i)
{
	xv.push_back(100);
	xv.push_back(i);
	xv.push_back(30);
}


B::~B()
{
}

vector<double>& B::GetXv()
{
	return xv;
}
