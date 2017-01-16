#include <iostream>

#include "TFile.h"
#include "TObjArray.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TROOT.h"

using namespace std;

int main(int argc, char *argv[])
{
	
	
	////save
	//TFile f_tree("D:\\Data_work\\test_folder\\test_save.root", "RECREATE");
	//TTree tree("t1", "Parser tree save");
	//TCanvas canv("c", "c", 0, 0, 1900, 1000);
	//tree.Branch("canvas_tr", "TCanvas", &canv);
	//tree.Fill();
	//tree.Write();
	//f_tree.Close();

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
	return 0;
}