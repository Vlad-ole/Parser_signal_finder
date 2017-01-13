//#include <iostream>
//#include <sstream>
//#include <vector>
//#include <iomanip>
//#include <fstream>
//
//#include "TF1.h"
//#include "TGraph.h"
//#include "TFile.h"
//#include "TRandom.h"
//#include "TMath.h"
//#include "TObjArray.h"
//#include "TGraphErrors.h"
//#include "TFile.h"
//#include "TTree.h"
//#include "TCanvas.h"
//#include "TChain.h"
//#include "TROOT.h"
//
//int main(int argc, char *argv[])
//{
//
//	TObjArray Hlist_gr(0);
//	Hlist_gr.SetOwner(kTRUE);
//
//	TCanvas* canv_read = 0;
//
//	TChain chain("t1");
//	chain.Add("D:\\Data_work\\test_folder\\test_save.root");
//	chain.SetBranchAddress("canvas_tr", &canv_read);
//
//	chain.GetEntry(0);
//	Hlist_gr.Add(canv_read->Clone());
//
//	TFile ofile_Hlist_gr("D:\\Data_work\\test_folder\\test_result.root", "RECREATE");
//	Hlist_gr.Write();
//	ofile_Hlist_gr.Close();
//
//	system("pause");
//	return 0;
//}