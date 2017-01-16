#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

#include "ReadData.h"
#include "WriteTree.h"
#include "CalcData.h"

#include "TApplication.h"
#include "TROOT.h"

using namespace std;

int main(int argc, char *argv[])
{
	TApplication theApp("theApp", &argc, argv);//let's add some magic! https://root.cern.ch/phpBB3/viewtopic.php?f=3&t=22972
	gROOT->SetBatch(kTRUE);
	
	const string path_name = "D:\\Data_work\\161026\\run3\\";
	vector<ch_info> ch_list;
	ch_list.resize(2);
	
	ch_list[0].id = 1;
	ch_list[0].VERTICAL_OFFSET = -0.294999986886978;
	ch_list[0].VERTICAL_GAIN = 0.0000124943999253446;

	ch_list[1].id = 3;
	ch_list[1].VERTICAL_OFFSET = -3.04999995231628;
	ch_list[1].VERTICAL_GAIN = 0.000124943995615467;

	comm_info str_comm;
	str_comm.write_type = 4096;
	str_comm.time_offset = 40;//us
	str_comm.HORIZ_INTERVAL = 5;//ns per point;


	WriteTree *wrt = NULL;

	const int events_per_file = 100;
	const int start_event_number = 1;
	const int stop_event_number = 10;
	for (int event_number = start_event_number; event_number <= stop_event_number; event_number++)
	{
		ReadData rdt(path_name, event_number, ch_list, str_comm);
		CalcData calc_data( rdt.GetDataDouble(), rdt.GetTimeArray() );
		FillCanv fill_canv(calc_data);

		if ( (event_number - start_event_number) % events_per_file == 0)
			wrt = new WriteTree(path_name + "trees\\", calc_data, fill_canv);

		wrt->Fill();

		if ( ((event_number - start_event_number) % events_per_file == events_per_file - 1) || (event_number == stop_event_number) )
			delete wrt;

		cout << "event_number = " << event_number << endl;
	}
	
	cout << "all is ok" << endl;
	system("pause");
	theApp.Terminate();
	theApp.Run();
	return 0;
}