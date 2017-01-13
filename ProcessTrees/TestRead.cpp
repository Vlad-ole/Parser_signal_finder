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
#include "TGraph.h"


#include "TSystem.h"

void TestRead()
{
	TObjArray Hlist_gr(0);
	//Hlist_gr.SetOwner(kTRUE);

	TCanvas* canv_read = 0;

	TChain chain("t1");
	chain.Add("D:\\Data_work\\161026\\run3\\trees\\Block0000000.root"  /*"D:\\Data_work\\test_folder\\test_save.root"*/);
	chain.SetBranchAddress("canvas", &canv_read);

	chain.GetEntry(0);
	canv_read->DrawClone();
	//TGraph *gh = (TGraph*)canv_read->GetListOfPrimitives()->FindObject("Graph");
	//gh->Draw();

	canv_read->ls();
}