#pragma once

#include <iostream>
#include <vector>

class FindS2
{
public:
	FindS2(std::vector<int>& peak_position, const int n_points, double HORIZ_INTERVAL, const double time_th);
	~FindS2();
	int GetPointS2Left();
	int GetPointS2Right();
private:
	int point_s2_left;
	int point_s2_right;
};

