#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>



#include "TFile.h"
#include "TObjArray.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TROOT.h"

#include "TSystem.h"


int main(int argc, char *argv[])
{
	//TObjArray Hlist_gr(0);
	//Hlist_gr.SetOwner(kTRUE);

	//TCanvas* canv_read = 0;

	//TChain chain("t1");
	//chain.Add("D:\\Data_work\\161026\\run3\\trees\\Block0000000.root");
	//chain.SetBranchAddress("canvas", &canv_read);

	//chain.GetEntry(0);
	//Hlist_gr.Add(canv_read->Clone());

	//TFile ofile_Hlist_gr("D:\\Data_work\\test_folder\\test_result.root", "RECREATE");
	//Hlist_gr.Write();
	//ofile_Hlist_gr.Close();

	system("pause");
	return 0;
}
