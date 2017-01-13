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
//	TFile f_tree("D:\\Data_work\\test_folder\\test_save.root", "RECREATE");
//	TTree tree("t1", "Parser tree save");
//
//	TCanvas canv("c", "c", 0, 0, 1900, 1000);
//	tree.Branch("canvas_tr", "TCanvas", &canv);
//
//	tree.Fill();
//	tree.Write();
//
//	f_tree.Close();
//
//	system("pause");
//	return 0;
//}
//
