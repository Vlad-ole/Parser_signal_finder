#pragma once

#include "TCanvas.h"

class Canv
{
public:
	Canv();
	~Canv();
	TCanvas &GetCanv();
private:
	TCanvas canv;
};

