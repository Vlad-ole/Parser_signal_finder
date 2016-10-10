void test()
{
	string dir_name = "D:\\Data_work\\res.root";
	
	TObjArray Hlist_gr(0);
	Hlist_gr.SetOwner(kTRUE);
	
	TCanvas* canv = new TCanvas("c", "c", 0, 0, 190, 100);
	
	Hlist_gr.Add(canv->Clone());
	
	TFile ofile_Hlist_gr(dir_name.c_str(), "RECREATE");
	Hlist_gr.Write();
	ofile_Hlist_gr.Close();
}