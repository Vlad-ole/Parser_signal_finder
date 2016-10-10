#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

#include "TF1.h"
#include "TGraph.h"
#include "TFile.h"

#include "TRandom.h"
#include "TMath.h"
#include "TObjArray.h"
#include "TGraphErrors.h"
#include  "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"

#include "Func.h"
#include "Golay_filter.h"
#include "Input_Output.h"
#include "Baseline_calc.h"

#define write_trees

using namespace std;


int main(int argc, char *argv[])
{
	vector<double> xv;

	const int vsize = 20000;
	const double time_scale = 5; //[ns / point]	
	const double voltage_scale_c1 = 0.5; //[V / div]
	const double voltage_scale_c3 = 0.2; //[V / div]
	const bool show_graphs = false;
	const string dir_name = "D://Data_work//161005//run_1_n//";


	const int n_start = 0;
	const int n_of_files = 1;

	for (int number_of_file = n_start; number_of_file < n_start + n_of_files; number_of_file++)
	{
	
		//create root tree

		string dir_trees = dir_name + "trees//";
		ostringstream file_tree_oss;
		file_tree_oss << dir_trees << "run_" << setfill('0') << setw(5) << number_of_file << ".root";
		TFile f_tree(file_tree_oss.str().c_str(), "RECREATE");
		TTree tree("t1", "Parser tree");

		TCanvas canv("c", "c", 0, 0, 1900, 1000);
		tree.Branch("canvas_tr", "TCanvas", &canv);

		tree.Fill();
		tree.Write();

	}


	system("pause");
	return 0;
}






