#include <iostream>
#include <vector>
#include <algorithm>

#include "TFile.h"
#include "TTree.h"
#include "TObjArray.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TROOT.h"

#include "Canv.h"
#include "D.h"

using namespace std;

int main(int argc, char *argv[])
{
	TApplication theApp("theApp", &argc, argv);
	gROOT->SetBatch(kTRUE);
	
	TFile *f_tree = new TFile("D:\\Data_work\\test_folder\\test_write.root", "RECREATE");
	TTree tree("t1", "Parser tree");

	//double x;
	//tree.Branch("x", &x, "x/D");
	////cout << "&x = " << &x << endl;
	//for (int i = 0; i < 100; i++)
	//{
	//	
	//	x = i;
	//	tree.Fill();

	//	if (i % 100 == 0)
	//		cout << "i = " << i << endl;
	//}

	//TCanvas canv;
	//tree.Branch("canvas", "TCanvas", &canv);
	//for (int i = 0; i < 100; i++)
	//{		
	//	Canv canv_from_obj;
	//	canv = canv_from_obj.GetCanv();
	//	tree.Fill();

	//	if (i % 100 == 0)
	//		cout << "i = " << i << endl;
	//}

	//for (int i = 0; i < 100; i++)
	//{
	//	Canv canv_from_obj;
	//	tree.Branch("canvas", "TCanvas", &( canv_from_obj.GetCanv() ) );
	//	tree.Fill();

	//	if (i % 100 == 0)
	//		cout << "i = " << i << endl;
	//}

	//for (int i = 0; i < 100; i++)
	//{
	//	D d;
	//	tree.Branch("x", &( d.GetX() ), "x/D" );
	//	tree.Fill();

	//	if (i % 100 == 0)
	//		cout << "i = " << i << endl;
	//}



	for (int i = 0; i < 1000; i++)
	{
		double x;
		x = i;
		tree.Branch("x", &x, "x/D");

		if (i % 100 == 0)
			cout << "i = " << i << endl;		
		
		tree.Fill();

		tree.ResetBranchAddresses();
	}



	//for (int i = 0; i < 10; i++)
	//{
	//	B b(i);
	//	tree.Branch("x", &(b.GetXv()[1]), "x/D");
	//	cout << "&x = " << &(b.GetXv()[1]) << endl;
	//	tree.Fill();
	//}
	
	tree.Write();
	f_tree->Close();
	
	
	cout << "all is ok" << endl;
	system("pause");
	theApp.Terminate();
	theApp.Run();

	return 0;
}