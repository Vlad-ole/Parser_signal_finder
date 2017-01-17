#include <iostream>
#include <sstream>
#include <iomanip>

#include "WriteTree.h"

using namespace std;

unsigned int WriteTree::counter_f_tree = 0;

WriteTree::WriteTree(const std::string path_name) :	path_name(path_name), tree("t1", "Parser tree")
{
	//create file name to write root tree
	ostringstream file_tree_oss;
	file_tree_oss << path_name << "Block" << setfill('0') << setw(7) << counter_f_tree << ".root";

	f_tree = new TFile(file_tree_oss.str().c_str(), "RECREATE");


	
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

void WriteTree::Fill(CalcData &calc_data, FillCanv &fill_canv)
{
	tree.Branch("baseline_ch0", &calc_data.GetBaseline()[0], "baseline_ch0/D");
	tree.Branch("baseline_ch1", &calc_data.GetBaseline()[1], "baseline_ch1/D");

	tree.Branch("min_ch0", &calc_data.GetMin()[0], "min_ch0/D");
	tree.Branch("min_ch1", &calc_data.GetMin()[1], "min_ch1/D");

	tree.Branch("max_ch0", &calc_data.GetMax()[0], "max_ch0/D");
	tree.Branch("max_ch1", &calc_data.GetMax()[1], "max_ch1/D");

	tree.Branch("canvas", "TCanvas", &fill_canv.GetCanv());	
	
	cout << calc_data.GetMin()[0] << " " << calc_data.GetMin()[1] << " " << calc_data.GetMax()[0] << " " << calc_data.GetMax()[1] << endl;
	cout << "write vars with the next adresses: " << endl;
	cout << &calc_data.GetMin()[0] << " " << &calc_data.GetMin()[1] << " " << &calc_data.GetMax()[0] << " " << &calc_data.GetMax()[1] << endl << endl;
	tree.Fill();
}
