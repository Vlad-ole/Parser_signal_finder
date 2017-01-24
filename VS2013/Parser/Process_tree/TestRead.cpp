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

#include "TApplication.h"
#include "TSystem.h"

using namespace std;

//void TestRead(int n_event = 0)
int main(int argc, char *argv[])
{
	TApplication theApp("theApp", &argc, argv);//let's add some magic! https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=22972
	gROOT->SetBatch(kTRUE);
	
	TObjArray Hlist_gr(0);
	Hlist_gr.SetOwner(kTRUE);

	TCanvas* canv_read = 0;

	TChain chain("t1");
	chain.Add("D:\\Data_work\\161026\\run3\\trees\\Block0000000.root"  /*"D:\\Data_work\\test_folder\\test_save.root"*/);
	chain.SetBranchAddress("canvas", &canv_read);
	
	std::cout << "chain.GetEntries() = " << chain.GetEntries() << std::endl;
	for (int i = 0; i < chain.GetEntries(); i++)//some promlems here
	{
		chain.GetEntry(i);
		//canv_read->ls();
		//canv_read->DrawClone();
		Hlist_gr.Add( canv_read->Clone() );
	}
		
	TFile ofile_Hlist_gr("D:\\Data_work\\161026\\run3\\result.root", "RECREATE");
	Hlist_gr.Write();
	ofile_Hlist_gr.Close();

	cout << "all is ok" << endl;
	system("pause");
	theApp.Terminate();
	theApp.Run();

}