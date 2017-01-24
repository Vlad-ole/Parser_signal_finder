#include "Canv.h"

Canv::Canv() : canv("c", "c", 0, 0, 190, 100)
{
}


Canv::~Canv()
{
}

TCanvas &Canv::GetCanv()
{
	return canv;
}
