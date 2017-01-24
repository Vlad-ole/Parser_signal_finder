#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "TFile.h"
#include "TTree.h"
#include "TObjArray.h"
#include "CalcData.h"
#include "FillCanv.h"

class WriteTree
{
public:
	WriteTree(const std::string path_name);
	~WriteTree();

	void GenerateBranches();
	void Fill(CalcData &calc_data, FillCanv &fill_canv);
private:
	TFile *f_tree;
	TTree tree;
	const std::string path_name;
	static unsigned int counter_f_tree;
};

