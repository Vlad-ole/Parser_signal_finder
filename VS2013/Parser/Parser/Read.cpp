#include <iostream>

#include "TFile.h"
#include "TObjArray.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TROOT.h"

#include "TApplication.h"

using namespace std;

int main(int argc, char *argv[])
{
	TApplication theApp("theApp", &argc, argv);// https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=22972
	
	//read
	TObjArray Hlist_gr(0);
	Hlist_gr.SetOwner(kTRUE);
	TCanvas* canv_read = 0;
	TChain chain("t1");
	chain.Add("D:\\Data_work\\test_folder\\test_save.root");
	chain.SetBranchAddress("canvas_tr", &canv_read);
	chain.GetEntry(0);
	Hlist_gr.Add(canv_read->Clone());
	TFile ofile_Hlist_gr("D:\\Data_work\\test_folder\\test_result.root", "RECREATE");
	Hlist_gr.Write();
	ofile_Hlist_gr.Close();

	system("pause");
	theApp.Terminate();
	theApp.Run();
	return 0;
}