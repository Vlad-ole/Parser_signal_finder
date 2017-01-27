#pragma once

#include <iostream>
#include <vector>

class PeakFinder
{
public:
	PeakFinder(std::vector<double>& yv, std::vector<double>& time, const double th);
	~PeakFinder();
	std::vector<int>& GetPeakPosition();
private:
	std::vector<int> peak_position;
};

