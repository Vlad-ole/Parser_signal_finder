#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

TGraph * gr0;
vector<double> t_start_V;
vector<double> t_stop_V;

Double_t fit_exp(Double_t *x,Double_t *par) 
{ 
	Double_t time = x[0] - par[2]; 
	Double_t fitval;
	if (time > 0) 
	{
		fitval = par[0] + par[1]*TMath::Exp(-time / par[3]); 
		//cout << "time > 0 \t x[0] = " << x[0] << "\t " << par[1]*TMath::Exp(-x[0] / par[3]) << "\t" <<  << endl;
	}
	else
	{
		fitval = par[0];
		//cout << "time < 0" << endl;
	}
	
	return fitval;
}

//integral of signal
vector<double> integral_vs_time(vector<double> yv, double baseline, double dt)
{
	vector<double> yv_result;
	yv_result.resize(yv.size());
	double summ = 0;
	
	for(int i = 0; i < yv.size(); i++)
	{
		summ += (yv[i] - baseline);
		yv_result[i] = summ * dt;
	}
	
	//cout << yv_result[0] << "\t" << yv_result[100] << "\t" << yv_result[200] << endl;
	
	return yv_result;
}


// advanced integral of signal
vector<double> integral_vs_time(vector<double> xv_, vector<double> yv, vector<double> yv_der, double dt, double th, double dead_time)
{
	vector<double> yv_result;
	vector<double> baselineV;
	vector<double> baselineV_single;
	yv_result.resize(yv.size());
	baselineV.resize(yv.size());
	double summ = 0;
	double shift = 0; //ns
	bool flag = true;
	double time_trigg;
	t_start_V.resize(0);
	t_stop_V.resize(0);
	
	vector<TF1*> TF1V;
	vector<string> stringV;
	vector<double> par0V;
	
	//find start and stop for future fitting
	t_start_V.push_back(1000); // range 0 - 1000 ns is noisy 
	double time_max = 60000; //ns
	int point_max = (int)(time_max / dt);
	for(int i = 0; i < point_max; i++)
	{
		if(yv_der[i] > th && flag)
		{
			t_stop_V.push_back(dt * i - shift); //[ns]
			flag = false;
			time_trigg = dt * i;
		}

		if( i * dt > (time_trigg + dead_time) && !flag )
		{
			flag = true;
			t_start_V.push_back(dt * i - shift);
		}
		
		if(yv_der[i] < th && flag && ( i == point_max - 1) )
		{
			t_stop_V.push_back(dt * i);
		}
		
	}
	
	gr0 = new TGraph(yv.size(), &xv_[0], &yv[0]);
	
	bool the_first = true;
	//calculate and set baseline
	for(int i=0; i < t_start_V.size(); i++)
	{
		stringstream ss;
		ss << "f" << i;
		string tf1_name = ss.str();
		TF1* f = new TF1(tf1_name.c_str(), "[0]", t_start_V[i], t_stop_V[i]);
		cout << "tf1_name = " << tf1_name << endl;
		
		if(the_first)
		{
			gr0->Fit(tf1_name.c_str(), "R");
			the_first = false;
		}
		else
		{
			gr0->Fit(tf1_name.c_str(), "R+");
		}
		
		baselineV_single.push_back(f->GetParameter(0));
	
	}
	
	t_start_V[0] = 0;
	for(int i=0; i < t_start_V.size() - 1; i++)
	{
		for(int j = (int)(t_start_V[i] / dt); j < (int)( t_start_V[i+1] / dt); j++)
		{
			baselineV[j] = baselineV_single[i];
		}
	}
	for(int i = (int)(t_start_V[t_start_V.size() - 1] / dt); i < yv.size(); i++)
	{
		baselineV[i] = baselineV_single[t_start_V.size() - 1];
	}
	
/* 	for(int j = point_max; j < yv.size(); j++)
	{
		baselineV[j] = baselineV_single[t_start_V.size() - 1];
	} */

/* 	//view control
	for(int i=0; i < t_start_V.size(); i++)
	{
		cout << "baselineV_single = " << baselineV_single[i] << endl;
	}
	
	//view control
 	for(int i = (int)(0 / dt); i < (int)(100000 / dt); i+=1000)
	{
		cout << i*dt << "\t" << baselineV[i] << endl;
	}  */
	
	//calculate integral
	for(int i = 0; i < yv.size(); i++)
	{
		summ += (yv[i] - baselineV[i]);
		yv_result[i] = summ * dt;
		
	}

	
	//cout << yv_result[0] << "\t" << yv_result[100] << "\t" << yv_result[200] << endl;
	
	return yv_result;
}




//Calculate Filter Coeff for (Savitzky–Golay filter)
vector<double> CalculateFilterCoeff(int points)
{
	cout << endl << "start Calculate filter coefficients" << endl;
	
	//Savitzky–Golay filter
	//order = 3
	
	vector<double> C_i_der;
	int m = points;//

	//ïîñ÷èòàòü êîýôôèöèåíòû  C_i
	for (int i = (1 - m) / 2.0; i <= (m - 1) / 2.0; i++)
	{
		double numerator = 5 * (3 * pow(m, 4.0) - 18 * pow(m, 2.0) + 31)*i - 28 * (3 * pow(m, 2.0) - 7)*pow(i, 3.0);
		double denominator = m * (pow(m, 2.0) - 1) * (3 * pow(m, 4.0) - 39 * pow(m, 2.0) + 108) / 15.0;
		C_i_der.push_back(numerator / denominator);
	}
	cout << endl << "stop Calculate filter coefficients" << endl;
	return C_i_der;
}

//Calculate Derivative (Savitzky–Golay filter)
vector<double> CalculateDerivative(vector<double> yv, int points)
{
	cout << endl << "start Calculate Derivatives" << endl;
	
	vector<double> C_i_der = CalculateFilterCoeff(points);
	
	
	vector<double> yv_der;
	const int point_half = (points - 1) / 2.0;
	yv_der.resize(yv.size());

#pragma omp parallel for num_threads(8)
	for (int i = 0; i < yv.size(); i++)
	{

		if (i < point_half || i >(yv.size() - point_half - 1))
		{
			yv_der[i] = 0;
		}
		else
		{
			double value = 0;
			for (int j = 0; j < C_i_der.size(); j++)
			{
				value += C_i_der[j] * yv[i - point_half + j];
			}
			yv_der[i] = value;

		}

	}
	
	cout << endl << "stop Calculate Derivatives" << endl;
	
	return yv_der;
}


void graph_LeCroy_binary(unsigned int number_of_file, unsigned int type_of_file, int vsize)
{
	vector<double> xv_;
	
	vector<unsigned char> yv_one_byte;
	vector<unsigned short int> yv_two_byte;
	vector<double> yv_double;
	//int vsize = 500;
	double time_scale = 2; //[ns / point]

	
	//string dir_name = "D://Data_work//run_3_Am//";
	string dir_name = "D://Data_work//run_3_Am//";
	
	ostringstream f_oss;
	f_oss << dir_name << "C1Trace" << setfill('0') << setw(5) <<  number_of_file << ".trc"; //my PC
	FILE *f = fopen(f_oss.str().c_str(), "rb");
	if (f == NULL)
	{
		cout << "Can't open this file: " << f_oss.str().c_str() << endl;
		//system("pause");
		fclose(f);
		exit(1);
	}
	else
	{
		cout << f_oss.str() << endl;
	}

	if(type_of_file == 1)
	{
		yv_one_byte.resize(vsize);
		fread(&yv_one_byte[0], sizeof(vector<unsigned char>::value_type), vsize, f);
	}
	if(type_of_file == 2)
	{
		yv_two_byte.resize(vsize);	
		fread(&yv_two_byte[0], sizeof(vector<unsigned short int>::value_type), vsize, f);
	}
	
	//x points to ns
	xv_.resize(vsize);
	for (int i = 0; i < vsize; i++)
	{
		xv_[i] = time_scale * i;
	}

	//y points to volts
	yv_double.resize(vsize);
	for (int i = 0; i < vsize; i++)
	{
		if(type_of_file == 1)
			yv_double[i] = (double)yv_one_byte[i];
		
		int real_value;
		if(type_of_file == 2)
		{
			real_value = yv_two_byte[i] >> 4;
			yv_double[i] = (double)real_value;
		}
		
		double V_max = 4;
		double k = V_max / 127.0 ;
		double b = -V_max * (1 + 128.0 / 127);
		//convert ADC code to Voltage
		if( yv_double[i] >=0 && yv_double[i] <= 127)
			yv_double[i] *= k;
		else if( yv_double[i] >= 128 && yv_double[i] <= 255)
			yv_double[i] = k * yv_double[i] + b;
		else
			cout << "error in convert ADC code to Voltage" << endl;
		
	}
	
	//There strange noise in the start of the signal.
	//For right double integration we have to rewrite this noise to baseline value   
	for(int i=0; i < 400; i++)
	{
		yv_double[i] = -2.9;
	}
	
	//calculate derivative (Savitzky–Golay filter)
	const int points = 101; //this number must be odd!!! 101 points -> 202 ns ~ tau of PMT signal
	vector<double> yv_der = CalculateDerivative(yv_double, points);
	
	
		
	//integral_vs_time
	vector<double> yv_integral;
	yv_integral.resize(vsize);
	double th = 3E-3; // threshold for derivative [V / ns]
	double dead_time = 1000; //[ns]
	//yv_integral = integral_vs_time(yv_double, baseline, dt);//[V * ns] 
	yv_integral = integral_vs_time(xv_, yv_double, yv_der, time_scale, th, dead_time);//[V * ns] advanced
	
	cout << "t_start_V.size() = " << t_start_V.size() << endl;
	
	//fit S1 signal
	TF1 fitFcn("fitFcn", fit_exp, t_stop_V[0], t_start_V[1], 4);
	if(t_stop_V[0] < 59000)
	{
		//fitFcn = new TF1("fitFcn", fit_exp, t_stop_V[0], t_start_V[1], 4);
		fitFcn.SetLineColor(3);
		
		fitFcn.SetParLimits(0, -2.92442, -2.92442);
		fitFcn.SetParLimits(1, 0, 10); 
		fitFcn.SetParLimits(2, t_stop_V[0], t_start_V[1]);
		fitFcn.SetParLimits(3, 150, 200);//ns 		
		
		
		fitFcn.SetParameter(0, -2.92442);
		fitFcn.SetParameter(1, 0.5);
		fitFcn.SetParameter(2, t_stop_V[0]);
		fitFcn.SetParameter(3, 100);
		gr0->Fit("fitFcn", "R+");		
	}
	
	
	//rough estimate of S2 
	double integral_max = 0;
	for(int i = (int)(60000 / time_scale); i < (int)(100000 / time_scale); i++)
	{
		if(yv_integral[i] > integral_max)
			integral_max = yv_integral[i];
	}
	
	cout << "S2 = " << integral_max << "\t S1 = " <<  fitFcn.GetParameter(1) * fitFcn.GetParameter(3) << endl;
	
	//view control
	for(int i = 0; i < t_start_V.size(); i++)
	{
		cout << t_start_V[i] << "\t" << t_stop_V[i] << endl;
	}
	
	ofstream file_out_det("D://Data_work//Am_results_in_detail.dat");
	file_out_det << fitFcn.GetParameter(0) << "\t" << fitFcn.GetParameter(1) << "\t" << fitFcn.GetParameter(2) << "\t" << 
	fitFcn.GetParameter(3) <<  "\t" << integral_max << endl;
	
	ofstream file_out_short("D://Data_work//Am_results_short.dat");
	file_out_short <<  fitFcn.GetParameter(1) * fitFcn.GetParameter(3)  << "\t" << integral_max << endl;

	
	file_out_det.close();
	file_out_short.close();
	
	
	//draw graphs 
	TCanvas *c = new TCanvas("c","c",0,0,1900,1000);
	c->Divide(2,2);

	c->cd(1);
	gr0->Draw();
	//fitFcn->Draw("same");
	
	c->cd(2);
	TGraph * gr2 = new TGraph(vsize, &xv_[0], &yv_integral[0]);
	gr2->SetMarkerColor(kRed);
	gr2->Draw();
	

	c->cd(3);
	TGraph * gr3 = new TGraph(vsize, &xv_[0], &yv_der[0]);
	gr3->Draw();

	
	
	
	
	
	//show individual bites
/* 	 for(int j=0; j < 40; j++)
	{
		
		if(type_of_file == 1)
		{
			unsigned short int val = yv_one_byte[j];
		}		
		if(type_of_file == 2)
		{
			unsigned short int val = yv_two_byte[j];
		}
		
		for(int i = 0; i < (8 * type_of_file); i++)
		{
			if( (val & pow(2, 8 * type_of_file)) == 0)
				cout << 0;
			else
				cout << 1;
			
			val <<= 1;
			
		}
		cout << endl;
	} */
	//cout << (double)(yv_two_byte[15] >> 4) << endl;

	//system("pause");
}