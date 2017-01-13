#include <iostream>
#include <sstream>
#include <iomanip>

#include "WriteTree.h"

using namespace std;

unsigned int WriteTree::counter_f_tree = 0;

WriteTree::WriteTree(const std::string path_name, CalcData &calc_data) : path_name(path_name), tree("t1", "Parser tree"), calc_data(calc_data)
{
	//create file name to write root tree
	ostringstream file_tree_oss;
	file_tree_oss << path_name << "Block" << setfill('0') << setw(7) << counter_f_tree << ".root";

	f_tree = new TFile(file_tree_oss.str().c_str(), "RECREATE");

	tree.Branch("baseline_ch1", &calc_data.baseline, "baseline_ch1/D");
	//
	//double xa[] = {1, 2, 3};
	//double ya[] = {11, 12, 13};
	//TGraph graph(3, &xa[0], &ya[0]);
	//graph.Draw("apl");

	tree.Branch("canvas", "TCanvas", calc_data.canv);
	//tree.Branch("canvas", "TCanvas", calc_data.canv);
	
	counter_f_tree++;	
}


WriteTree::~WriteTree()
{
	tree.Write();

	tree.ls();

	f_tree->Close();
	delete f_tree;
	f_tree = NULL;
}

void WriteTree::GenerateBranches()
{
	
}

void WriteTree::Fill()
{
	cout << "calc_data.baseline = " << calc_data.baseline << endl;
	
	tree.Fill();
}
