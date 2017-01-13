#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

#include "ReadData.h"
#include "WriteTree.h"
#include "CalcData.h"

using namespace std;

int main(int argc, char *argv[])
{
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
	for (int event_number = start_event_number; event_number <= 100; event_number++)
	{
		ReadData rdt(path_name, event_number, ch_list, str_comm);
		CalcData calc_data( rdt.GetDataDouble() );

		if ( (event_number - start_event_number) % events_per_file == 0)
			wrt = new WriteTree(path_name + "trees\\", calc_data);

		wrt->Fill();

		if ( (event_number - start_event_number) % events_per_file == events_per_file - 1)
			delete wrt;
	}
	
	
	cout << "all is ok" << endl;
	system("pause");
	return 0;
}