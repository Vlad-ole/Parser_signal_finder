#include <iostream>
#include <sstream>
#include <iomanip>

#include "WriteTree.h"

using namespace std;

unsigned int WriteTree::counter_f_tree = 0;

WriteTree::WriteTree(const std::string path_name, CalcData &calc_data, FillCanv &fill_canv) : 
	path_name(path_name), tree("t1", "Parser tree"), calc_data(calc_data), fill_canv(fill_canv)
{
	//create file name to write root tree
	ostringstream file_tree_oss;
	file_tree_oss << path_name << "Block" << setfill('0') << setw(7) << counter_f_tree << ".root";

	f_tree = new TFile(file_tree_oss.str().c_str(), "RECREATE");

	tree.Branch("baseline_ch1", &calc_data.GetBaseline()[0], "baseline_ch1/D");
	tree.Branch("canvas", "TCanvas", &fill_canv.GetCanv() );
	
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
	tree.Fill();
}
