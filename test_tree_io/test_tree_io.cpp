#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include "TMath.h"

#include "TApplication.h"
#include "TROOT.h"

#include "TH1F.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TSystem.h"

#include <iostream>
using namespace std;


void write()
{
	TFile *f = TFile::Open("D:\\Data_work\\test_folder\\hvector.root", "RECREATE");

	if (!f) { return; }

	std::vector<float> vpx;

	// Create a TTree
	TTree *t = new TTree("tvec", "Tree with vectors");
	t->Branch("vpx", &vpx);

	gRandom->SetSeed();
	for (Int_t i = 0; i < 2; i++)
	{
		Int_t npx = (Int_t)(gRandom->Rndm(1) * 15);

		vpx.clear();

		cout << "i = " << i << " ; npx = " << npx << endl;

		for (Int_t j = 0; j < npx; ++j) {

			Float_t px, py, pz;
			gRandom->Rannor(px, py);
			pz = px*px + py*py;
			Float_t random = gRandom->Rndm(1);

			cout << "\t" << j << " " << px << endl;
			vpx.push_back(px);
		}
		t->Fill();
	}
	f->Write();

	delete f;
}



void read()
{
	TFile *f = TFile::Open("D:\\Data_work\\test_folder\\hvector.root", "READ");

	if (!f) { return; }

	TTree *t; f->GetObject("tvec", t);

	std::vector<float> *vpx = 0;

	TBranch *bvpx = 0;
	t->SetBranchAddress("vpx", &vpx, &bvpx);

	for (Int_t i = 0; i < t->GetEntries(); i++)
	{

		Long64_t tentry = t->LoadTree(i);
		bvpx->GetEntry(tentry);

		cout << "i = " << i << " ; vpx->size() = " << vpx->size() << endl;

		for (UInt_t j = 0; j < vpx->size(); ++j)
		{
			cout << "vpx->at(" << j << ") = " << vpx->at(j) << endl;
		}
	}

	// Since we passed the address of a local variable we need
	// to remove it.
	t->ResetBranchAddresses();
}

int main(int argc, char *argv[])
{
	TApplication theApp("theApp", &argc, argv);
	gROOT->ProcessLine("#include <vector>");

	write();
	read();

	cout << "all is ok" << endl;
	system("pause");
	theApp.Terminate();
	theApp.Run();

	return 0;
}