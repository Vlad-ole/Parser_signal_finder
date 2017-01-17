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
	TChain chain("t1");
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


	const int n_events = chain.GetEntries();
	//const int n_events = 40;

	std::cout << "chain.GetEntries() = " << chain.GetEntries() << std::endl;
	for (int i = 0; i < n_events; i++)
	{
		chain.GetEntry(i);

		cout << baseline_ch0 << " " << baseline_ch1 << " " << min_ch0 << " " << min_ch1 << " " << max_ch0 << " " << max_ch1 << endl;

		TPad* pad = (TPad*)canv_read->GetListOfPrimitives()->FindObject("c_2");
		TGraph* gr = (TGraph*)pad->GetListOfPrimitives()->FindObject("Graph");

		if (pad == NULL || gr == NULL)
		{
			cout << "pad == NULL || gh == NULL" << endl;
			system("pause");
		}

		Hlist_gr.Add( gr->Clone() );
	}

	TCanvas* canv_write = new TCanvas("c", "c", 0, 0, 1900, 1000);
	for (int i = 0; i < n_events; i++)
	{
		TGraph* gr = (TGraph*) Hlist_gr.At(i);
		if (i == 0) gr->Draw();
		else gr->Draw("same");
	}

	TFile ofile_Hlist_gr("D:\\Data_work\\161026\\run3\\result.root", "RECREATE");
	canv_write->Write();
	ofile_Hlist_gr.Close();


	cout << "all is ok" << endl;
	system("pause");
	theApp.Terminate();
	theApp.Run();

}