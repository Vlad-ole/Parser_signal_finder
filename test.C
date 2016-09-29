#include <vector>
#include <TGraph>
#include <string>

void func()
{
	vector<double> xv;
	vector<double> yv;
	
	vector<TF1*> TF1V;
	vector<string> stringV;
	vector<double> par0V;
	
	TRandom* random1 = new TRandom;
	random1->SetSeed(5000);
	
	for(int i =0; i < 100; i++)
	{
		xv.push_back(i);
		yv.push_back(random1->Rndm());
	}
	
	TGraph* gr0 = new TGraph(yv.size(), &xv[0], &yv[0]);
	
	stringV.push_back("f1");
	stringV.push_back("f2");
	
	TF1V.push_back( new TF1(stringV[0].c_str(), "[0]", 0, 20) );
	TF1V.push_back( new TF1(stringV[1].c_str(), "[0]", 60, 80) );
	
	gr0->Fit("f1", "R");
	gr0->Fit("f2", "R+");
	
	par0V.push_back( TF1V[0]->GetParameter(0) );
	par0V.push_back( TF1V[1]->GetParameter(0) );
	
	
	cout <<  par0V[0] << "\t" << par0V[1] << endl;
	//TGraph* gr0 = new TGraph(yv.size(), &xv[0], &yv[0]);
	/* TF1 *f1 = new TF1("f1", "[0]", 0, 20);
	TF1 *f2 = new TF1("f2", "[0]", 60, 80);
	gr0->Fit("f1", "R");
	gr0->Fit("f2", "R+"); */
	
/* 	double par0 = f1->GetParameter(0);
	gr0->GetListOfFunctions()->Add(f1);
	gROOT->GetListOfFunctions()->Remove(f1);
	
	TF1 *f2 = new TF1("f2", "[0]", 60, 80);
	gr0->Fit("f2", "R");
	par0 = f2->GetParameter(0);
	gr0->GetListOfFunctions()->Add(f2);
	gROOT->GetListOfFunctions()->Remove(f2); */
	//gr0->GetListOfFunctions()->Add(f2);
	//gROOT->GetListOfFunctions()->Remove(f2);
	
	//gr0->Fit("f1", "R");
	//gr0->Fit("f2", "R");
	
	gr0->Draw();
	
	//cout << f->GetParameter(0) << endl;
	
}