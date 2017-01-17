#include <iostream>
#include <vector>
#include <algorithm>

#include "A.h"
#include "B.h"

#include "TFile.h"
#include "TTree.h"
#include "TObjArray.h"


using namespace std;

int main(int argc, char *argv[])
{
	TFile *f_tree = new TFile("D:\\Data_work\\test_folder\\test_write.root", "RECREATE");
	TTree tree("t1", "Parser tree");

	//double x;
	//tree.Branch("x", &x, "x/D");
	//cout << "&x = " << &x << endl;

	//for (int i = 0; i < 10; i++)
	//{
	//	x = i;
	//	tree.Fill();
	//}

	//for (int i = 0; i < 10; i++)
	//{
	//	double x;
	//	tree.Branch("x", &x, "x/D");
	//	cout << "&x = " << &x << endl;
	//	x = i;
	//	tree.Fill();
	//}

	for (int i = 0; i < 10; i++)
	{
		B b(i);
		tree.Branch("x", &(b.GetXv()[1]), "x/D");
		cout << "&x = " << &(b.GetXv()[1]) << endl;
		tree.Fill();
	}
	
	tree.Write();
	f_tree->Close();
	
	
	cout << "all is ok" << endl;
	system("pause");
	return 0;
}