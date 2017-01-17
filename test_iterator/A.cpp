#include "A.h"



A::A(vector< vector<double> >& data) : data(data)
{
	const int n_ch = data.size();

	vector<double>::const_iterator it_b_0 = data[0].begin();
	vector<double>::const_iterator it_e_0 = data[0].end();
	vector<double>::const_iterator it_b_1 = data[1].begin();
	vector<double>::const_iterator it_e_1 = data[1].end();

	min.resize(n_ch);
	min[0] = *min_element(it_b_0, it_e_0);
	min[1] = *min_element(it_b_1, it_e_1);

	max.resize(n_ch);
	max[0] = *max_element(it_b_0, it_e_0);
	max[1] = *max_element(it_b_1, it_e_1);

	//cout << "min[0] = " << min[0] << endl;
	//cout << "min[1] = " << min[1] << endl;

	//cout << "max[0] = " << max[0] << endl;
	//cout << "max[1] = " << max[1] << endl;
}


A::~A()
{
}
