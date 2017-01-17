#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class A
{
public:
	A(vector< vector<double> >& data);
	~A();
private:
	vector< vector<double> >& data;

	std::vector<double> max;
	std::vector<double> min;
};

