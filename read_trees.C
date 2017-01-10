void ReadTree()
{
	
	
	string dir_name = "D:\\Data_work\\161005\\run_1_n\\trees\\";
	string graph_name = dir_name + "results\\graphs_fit1.root";
	
	TObjArray Hlist_gr(0);
	Hlist_gr.SetOwner(kTRUE);

	TCanvas* canv = 0;
	
	TChain chain("t1");// name of the tree is the argument
	//const int n_max = 22426; //Am
	const int n_max = 100; //for tests
	for(int i = 0; i < n_max; i++)
	{
		ostringstream file_tree_oss;
		file_tree_oss << dir_name << "run_" << setfill('0') << setw(5) << i << ".root";
		chain.Add(file_tree_oss.str().c_str());
	}
	
	chain.SetBranchAddress("canvas_tr", &canv);
	
	double baseline_par_br, amp_par_br, start_time_par_br, tau_par_br;//fit params
	double s2_area_br;
	chain.SetBranchAddress("baseline_par_br", &baseline_par_br);
	chain.SetBranchAddress("amp_par_br", &amp_par_br);
	chain.SetBranchAddress("start_time_par_br", &start_time_par_br);
	chain.SetBranchAddress("tau_par_br", &tau_par_br);
	chain.SetBranchAddress("s2_area_br", &s2_area_br);
	
	TCut total_cut = "amp_par_br > 0.3";
	//TCut total_cut = "(amp_par_br * tau_par_br < 100) && (amp_par_br * tau_par_br > 1)";

	chain.SetMarkerStyle(4);
	
	//chain.Draw("amp_par_br * tau_par_br", total_cut);	
	chain.Draw("amp_par_br", total_cut);	
	
	
	if(true)
	{
		gROOT->SetBatch(kTRUE); // it's really important to use this line if you save TCanvas in a tree!
		for (int i = 0; i < chain.GetEntries() ; ++i)
		{
			chain.GetEntry(i);
			//bool condition = (amp_par_br * tau_par_br < 100) && (amp_par_br * tau_par_br > 1);
			//bool condition = true;
			if( amp_par_br > 0.3 )//condition
			{
				Hlist_gr.Add( canv->Clone() );
				//Hlist_gr.Add(graph->Clone());
			}
		}
		
		TFile ofile_Hlist_gr(graph_name.c_str(), "RECREATE");
		Hlist_gr.Write();
		ofile_Hlist_gr.Close();
	}
	
	
}

