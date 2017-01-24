#pragma once

#include "TChain.h"
#include "TCanvas.h"

class Chain
{
public:
	Chain();
	~Chain();
	int GetEntries();
	TCanvas &GetCanvas();
	void GetEntry(const int i);
private:
	TChain chain;
	TCanvas canv;
};

