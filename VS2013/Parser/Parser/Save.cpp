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
	//save
	TFile f_tree("D:\\Data_work\\test_folder\\test_save.root", "RECREATE");
	TTree tree("t1", "Parser tree save");
	TCanvas canv("c", "c", 0, 0, 1900, 1000);
	tree.Branch("canvas_tr", "TCanvas", &canv);
	tree.Fill();
	tree.Write();
	f_tree.Close();

	system("pause");
	return 0;
}