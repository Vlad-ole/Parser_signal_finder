#include "Chain.h"



Chain::Chain() : chain("t1")
{
	chain.Add("D:\\Data_work\\161026\\run3\\trees\\Block0000000.root");
	TCanvas* canv_read = 0;
	chain.SetBranchAddress("canvas", &canv_read);

	double baseline_ch0, baseline_ch1;
	double min_ch0, min_ch1;
	double max_ch0, max_ch1;

	chain.SetBranchAddress("baseline_ch0", &baseline_ch0);
	chain.SetBranchAddress("baseline_ch1", &baseline_ch1);

	chain.SetBranchAddress("min_ch0", &min_ch0);
	chain.SetBranchAddress("min_ch1", &min_ch1);

	chain.SetBranchAddress("max_ch0", &max_ch0);
	chain.SetBranchAddress("max_ch1", &max_ch1);
}


Chain::~Chain()
{
}

int Chain::GetEntries()
{
	return chain.GetEntries();
}

TCanvas & Chain::GetCanvas()
{
	return canv;
}

void Chain::GetEntry(const int i)
{
	chain.GetEntry(i);
}
