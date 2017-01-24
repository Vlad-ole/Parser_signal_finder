#pragma once

#include <iostream>
#include <vector>

class PeakFinder
{
public:
	PeakFinder(std::vector<double>& yv, std::vector<double>& time, const double th);
	~PeakFinder();
	std::vector<double>& GetPeakPosition();
private:
	std::vector<double> peak_position;
};

