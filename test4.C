void test_save()
{
	gROOT->SetBatch(kTRUE);
	
	//create & save tree
	//TFile f_tree("D:\\Data_work\\test_save.root", "RECREATE");// right var
	TFile f_tree("D://Data_work//test_save.root", "RECREATE");// work too
	TTree tree("t1", "Parser tree save");
	
	//TCanvas canv = 0;
	TCanvas canv("c", "c", 0, 0, 1900, 1000);
	canv.Divide(2,2);
	tree.Branch("canvas_tr", "TCanvas", &canv);
	
/* 	//fill points
	vector<double> xv;
	vector<double> yv;
	for(int i = 0; i < 10; i++)
	{
		xv.push_back(i);
		yv.push_back(i*i);
	}
	
	TGraph graph(yv.size(), &xv[0], &yv[0]);
	tree.Branch("gr_tr", "TGraph", &graph);
	
	canv.cd(1);
	graph.SetMarkerColor(kRed);
	graph.Draw();
	
	canv.cd(2);
	graph.SetMarkerColor(kBlue);
	graph.Draw();
	
	canv.cd(3);
	graph.SetMarkerColor(kGreen);
	graph.Draw(); */
	
	tree.Fill();
	tree.Write();
	
	//f_tree.Close();
	


}

void test_read()
{
	//read tree and save to watch
	TObjArray Hlist_gr(0);
	Hlist_gr.SetOwner(kTRUE);
	
	//TGraph* graph_read = 0;
	TCanvas* canv_read = 0;
	
	TChain chain("t1");
	chain.Add("D:\\Data_work\\test_save.root");	
	chain.SetBranchAddress("canvas_tr", &canv_read);
	//chain.SetBranchAddress("gr_tr", &graph_read);
	
	chain.GetEntry(0);
	Hlist_gr.Add(canv_read->Clone());
	//Hlist_gr.Add(graph_read->Clone());

	TFile ofile_Hlist_gr("D:\\Data_work\\test_read.root", "RECREATE");
	Hlist_gr.Write();
	ofile_Hlist_gr.Close();
}