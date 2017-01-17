#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class B
{
public:
	B(int i);
	~B();
	vector<double>& GetXv();
private:
	vector<double> yv;
	vector<double> xv;
	vector<double> zv;
};

