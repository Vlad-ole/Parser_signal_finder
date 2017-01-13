#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>


using namespace std;

struct WAVEDESC
{
	char DESCRIPTOR_NAME[27];//ok
	char TEMPLATE_NAME[16];//ok
	char COMM_TYPE[2];//ok
	char COMM_ORDER[2];//ok
	long int WAVE_DESCRIPTOR;
	long int USER_TEXT;
	long int RES_DESC1;
	long int TRIGTIME_ARRAY;
	long int RIS_TIME_ARRAY;
	long int RES_ARRAY1;
	long int WAVE_ARRAY_1;
	long int WAVE_ARRAY_2;
	long int RES_ARRAY2;
	long int RES_ARRAY3;
	char INSTRUMENT_NAME[16];//problem with first simbol, i.e. error before this line. But last sibmol is right
	long int INSTRUMENT_NUMBER;
	char TRACE_LABEL[16];
	short int RESERVED1;
	short int RESERVED2;
	long int WAVE_ARRAY_COUNT;
	long int PNTS_PER_SCREEN;
	long int FIRST_VALID_PNT;
	long int LAST_VALID_PNT;
	long int FIRST_POINT;
	long int SPARSING_FACTOR;
	long int SEGMENT_INDEX;
	long int SUBARRAY_COUNT;
	long int SWEEPS_PER_ACQ;
	short int POINTS_PER_PAIR;
	short int PAIR_OFFSET;
	float VERTICAL_GAIN;
	float VERTICAL_OFFSET;
	float MAX_VALUE;
	float MIN_VALUE;
	short int NOMINAL_BITS;
	short int NOM_SUBARRAY_COUNT;
	float HORIZ_INTERVAL;
	double HORIZ_OFFSET;
	double PIXEL_OFFSET;
	char VERTUNIT[48];
	char HORUNIT[48];
	float HORIZ_UNCERTAINTY;
	float TRIGGER_TIME;
	float ACQ_DURATION;
	char RECORD_TYPE;
	char PROCESSING_DONE;
	short int RESERVED5;
	short int RIS_SWEEPS;
	char TIMEBASE;
	char VERT_COUPLING;
	float PROBE_ATT;
	char FIXED_VERT_GAIN;
	char BANDWIDTH_LIMIT;
	float VERTICAL_VERNIER;
	float ACQ_VERT_OFFSET;
	char WAVE_SOURCE;
} Wavedesc;

int main(int argc, char *argv[])
{
	fstream file;
	file.open("D://Data_work//C1Trace00000.trc", ios::in | ios::binary);
	if (!file.is_open())
	{
		cout << "can't open this file: " << endl;
		system("pause");
		file.close();
		exit(1);
	}

	file.read((char*)& Wavedesc, sizeof(Wavedesc));

	cout << "Wavedesc.DESCRIPTOR_NAME = " << Wavedesc.DESCRIPTOR_NAME << endl;
	cout << "Wavedesc.TEMPLATE_NAME = " << Wavedesc.TEMPLATE_NAME << endl;
	cout << "Wavedesc.COMM_TYPE = " << (int)Wavedesc.COMM_TYPE[0] << endl;
	cout << "Wavedesc.COMM_ORDER = " << (int)Wavedesc.COMM_ORDER[0] << endl;
	cout << "Wavedesc.WAVE_DESCRIPTOR = " << Wavedesc.WAVE_DESCRIPTOR << endl;
	cout << "Wavedesc.USER_TEXT = " << Wavedesc.USER_TEXT << endl;
	cout << "Wavedesc.RES_DESC1 = " << Wavedesc.RES_DESC1 << endl;
	cout << "Wavedesc.TRIGTIME_ARRAY = " << Wavedesc.TRIGTIME_ARRAY << endl;
	cout << "Wavedesc.RIS_TIME_ARRAY = " << Wavedesc.RIS_TIME_ARRAY << endl;
	cout << "Wavedesc.RES_ARRAY1 = " << Wavedesc.RES_ARRAY1 << endl;
	cout << "Wavedesc.WAVE_ARRAY_1 = " << Wavedesc.WAVE_ARRAY_1 << endl;
	cout << "Wavedesc.WAVE_ARRAY_2 = " << Wavedesc.WAVE_ARRAY_2 << endl;
	cout << "Wavedesc.RES_ARRAY2 = " << Wavedesc.RES_ARRAY2 << endl;
	cout << "Wavedesc.RES_ARRAY3 = " << Wavedesc.RES_ARRAY3 << endl;
	cout << "Wavedesc.INSTRUMENT_NAME = " << Wavedesc.INSTRUMENT_NAME << endl;
	cout << "Wavedesc.INSTRUMENT_NUMBER = " << Wavedesc.INSTRUMENT_NUMBER << endl;
	cout << "Wavedesc.TRACE_LABEL = " << Wavedesc.TRACE_LABEL << endl;
	cout << "Wavedesc.RESERVED1 = " << Wavedesc.RESERVED1 << endl;
	cout << "Wavedesc.RESERVED2 = " << Wavedesc.RESERVED2 << endl;
	cout << "Wavedesc.WAVE_ARRAY_COUNT = " << Wavedesc.WAVE_ARRAY_COUNT << endl;
	cout << "Wavedesc.PNTS_PER_SCREEN = " << Wavedesc.PNTS_PER_SCREEN << endl;
	cout << "Wavedesc.FIRST_VALID_PNT = " << Wavedesc.FIRST_VALID_PNT << endl;
	cout << "Wavedesc.LAST_VALID_PNT = " << Wavedesc.LAST_VALID_PNT << endl;
	cout << "Wavedesc.FIRST_POINT = " << Wavedesc.FIRST_POINT << endl;
	cout << "Wavedesc.SPARSING_FACTOR = " << Wavedesc.SPARSING_FACTOR << endl;
	cout << "Wavedesc.SEGMENT_INDEX = " << Wavedesc.SEGMENT_INDEX << endl;
	cout << "Wavedesc.SUBARRAY_COUNT = " << Wavedesc.SUBARRAY_COUNT << endl;
	cout << "Wavedesc.SWEEPS_PER_ACQ = " << Wavedesc.SWEEPS_PER_ACQ << endl;
	cout << "Wavedesc.POINTS_PER_PAIR = " << Wavedesc.POINTS_PER_PAIR << endl;
	cout << "Wavedesc.PAIR_OFFSET = " << Wavedesc.PAIR_OFFSET << endl;
	cout << "Wavedesc.VERTICAL_GAIN = " << Wavedesc.VERTICAL_GAIN << endl;
	cout << "Wavedesc.VERTICAL_OFFSET = " << Wavedesc.VERTICAL_OFFSET << endl;
	cout << "Wavedesc.MAX_VALUE = " << Wavedesc.MAX_VALUE << endl;
	cout << "Wavedesc.MIN_VALUE = " << Wavedesc.MIN_VALUE << endl;
	cout << "Wavedesc.NOMINAL_BITS = " << Wavedesc.NOMINAL_BITS << endl;
	cout << "Wavedesc.NOM_SUBARRAY_COUNT = " << Wavedesc.NOM_SUBARRAY_COUNT << endl;
	cout << "Wavedesc.HORIZ_INTERVAL = " << Wavedesc.HORIZ_INTERVAL << endl;
	cout << "Wavedesc.HORIZ_OFFSET = " << Wavedesc.HORIZ_OFFSET << endl;
	cout << "Wavedesc.PIXEL_OFFSET = " << Wavedesc.PIXEL_OFFSET << endl;
	cout << "Wavedesc.VERTUNIT = " << Wavedesc.VERTUNIT << endl;
	cout << "Wavedesc.HORUNIT = " << Wavedesc.HORUNIT << endl;
	cout << "Wavedesc.HORIZ_UNCERTAINTY = " << Wavedesc.HORIZ_UNCERTAINTY << endl;
	cout << "Wavedesc.TRIGGER_TIME = " << Wavedesc.TRIGGER_TIME << endl;
	cout << "Wavedesc.ACQ_DURATION = " << Wavedesc.ACQ_DURATION << endl;
	cout << "Wavedesc.RECORD_TYPE = " << (int) Wavedesc.RECORD_TYPE << endl;
	cout << "Wavedesc.PROCESSING_DONE = " << (int)Wavedesc.PROCESSING_DONE << endl;
	cout << "Wavedesc.RESERVED5 = " << Wavedesc.RESERVED5 << endl;
	cout << "Wavedesc.RIS_SWEEPS = " << Wavedesc.RIS_SWEEPS << endl;
	cout << "Wavedesc.TIMEBASE = " << (int)Wavedesc.TIMEBASE << endl;
	cout << "Wavedesc.VERT_COUPLING = " << (int)Wavedesc.VERT_COUPLING << endl;
	cout << "Wavedesc.PROBE_ATT = " << Wavedesc.PROBE_ATT << endl;
	cout << "Wavedesc.FIXED_VERT_GAIN = " << (int)Wavedesc.FIXED_VERT_GAIN << endl;
	cout << "Wavedesc.BANDWIDTH_LIMIT = " << (int)Wavedesc.BANDWIDTH_LIMIT << endl;
	cout << "Wavedesc.VERTICAL_VERNIER = " << (int)Wavedesc.VERTICAL_VERNIER << endl;
	cout << "Wavedesc.WAVE_SOURCE = " << (int)Wavedesc.WAVE_SOURCE << endl;

	cout << "all is ok" << endl;
	system("pause");
	return 0;
}