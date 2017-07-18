#pragma once

#include <iostream>
#include <vector>

class PeakFinderBase
{
public:
	PeakFinderBase();
	virtual ~PeakFinderBase();
	std::vector<std::pair<int, int>> GetPeakPositions();
protected:
	std::vector<std::pair<int, int>> pair_v;
};

