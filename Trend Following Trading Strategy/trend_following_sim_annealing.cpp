#include <iostream>//author Wang, Jiakang; Walker, Sarah
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cstdlib>
#include <math.h>

#define MIN_CHANNEL 100
#define MAX_CHANNEL 10000

#define MIN_STOP .005
#define MAX_STOP .1

#define CHANNEL_INCREMENT 5
#define STOP_INCREMENT .001

#include <time.h>

using namespace std;


void sim_annealing(double temperature, double temperature_min, int k,vector<double>Open_data,vector<double>& Close_data,
	vector<double>& High_data,vector<double>& Low_data);

double trading(vector<double>& hh_data, vector<double>& ll_data, int channel_length, double stop_percentage,vector<double>& Open_data, vector<double>& Close_data, vector<double>& High_data, vector<double>& Low_data) {
	double High, Low, Open, Close, prev_peak, prev_trough,hh,ll,entry_price, deal_price, dd, ROA,current=0.0,peak=0.0,max_dd=0.0;
	int  channel_end=0, market_position=0, data_length=0, buy=0, sell=0, flg;
	//vector<double> current_list(Close_data.size(),0), max_list(Close_data.size(),0), channel_high, channel_low,dd_list(Close_data.size(), 0);
	data_length = Close_data.size() - channel_length;
	for (int channel_start= 17000 - channel_length; channel_start < data_length; channel_start++) {
		channel_end = channel_start + channel_length-1;
		Close = Close_data[channel_end];
		Open = Open_data[channel_end + 1];
		High = High_data[channel_end + 1];
		Low = Low_data[channel_end + 1];
		if (market_position == 0) {
			/*if (channel_start == (17000 - channel_length)) {
				hh = *max_element(High_data.begin() + channel_start, High_data.begin() + channel_end + 1);
				ll = *min_element(Low_data.begin() + channel_start, Low_data.begin() + channel_end + 1);
				prev_start = channel_start;
			}*/
			//else {
			//}
			hh = hh_data[channel_end + 1];
			ll = ll_data[channel_end + 1];
			if (Open >= hh) {
				entry_price = Open;
				//cout << Open << " " << channel_end << endl;
				market_position = 1;
				prev_peak = Open;
				buy = buy + 1;
				current = current + 42000 * (Close_data[channel_end + 1] - Open) - 23.5;
				flg = 0;
			}
			else if (High >= hh) {
				entry_price = hh;
				//cout << hh << " " << channel_end << endl;
				market_position = 1;
				prev_peak = hh;
				buy = buy + 1;
				current = current + 42000 * (Close_data[channel_end + 1] - hh) - 23.5;
				flg = 0;
			}

			else {
				flg = 1;
			}
			if (Open <= ll) {
				entry_price = Open;
				//cout << -Open << " " << channel_end << endl;
				market_position = -1;
				prev_trough = Open;
				sell = sell + 1;
				current = current - 42000 * (Close_data[channel_end + 1] - Open) - 23.5;
				flg = 0;
			}
			else if (Low <= ll) {
				entry_price = ll;
				//cout << -ll << " " << channel_end << endl;
				market_position = -1;
				prev_trough = ll;
				sell = sell + 1;
				current = current - 42000 * (Close_data[channel_end + 1] - ll) - 23.5;
				flg = 0;
			}
			else {
				if (flg == 1) {
					flg = 1;//zhihouzaixiangxiang
				}
			}
			if (flg == 1) {
				current = current;
			}
			if (flg == 0) {

				peak = max(peak, current);
				dd = peak - current;
				max_dd = max(max_dd, dd);
				continue;
			}
		}
		if (market_position > 0) {
			if (Close > prev_peak) {
				prev_peak = Close;
			}
			if (Open <= prev_peak*(1 - stop_percentage)) {
				deal_price = Open;
				market_position = 0;
				current = current + 42000 * (deal_price - Close) - 23.5;
				//cout << "**" << deal_price << " " << channel_end<<endl;
			}
			else if (Low <= prev_peak*(1 - stop_percentage)) {
				deal_price = prev_peak*(1 - stop_percentage);
				market_position = 0;
				current = current + 42000 * (deal_price - Close) - 23.5;
				//cout << "**" << deal_price << " " << channel_end<<endl;
			}
			else {
				current = current + 42000 * (Close_data[channel_end + 1] - Close);
			}
		}

		if (market_position < 0) {
			if (Close < prev_trough) {
				prev_trough = Close;
			}
			if (Open >= prev_trough*(1 + stop_percentage)) {
				deal_price = Open;
				market_position = 0;
				current = current - 42000 * (deal_price - Close) - 23.5;
				//cout << "**" << deal_price << " " << channel_end<<endl;
			}
			else if (High >= prev_trough*(1 + stop_percentage)) {
				deal_price = prev_trough*(1 + stop_percentage);
				market_position = 0;					
				current = current - 42000 * (deal_price - Close) - 23.5;
				//cout << "**" << deal_price << " " << channel_end<<endl;
			}
			else {
				current = current - 42000 * (Close_data[channel_end + 1] - Close);
			}
		}
		peak = max(peak, current);
		dd = peak - current;
		max_dd = max(max_dd, dd);
	}
	ROA = current / max_dd;
	//cout << current_list[Close_data.size() - 1] << " " << buy << " " << sell;
	//cout << ROA;
	return ROA;
}

vector<double> hhf(int channel_length, vector<double>& Open_data, vector<double>& Close_data, vector<double>& High_data, vector<double>& Low_data) {
	double hh;
	int channel_start,channel_end,data_length;
	hh = *max_element(High_data.begin() + 17000 - channel_length, High_data.begin() + 17000 + 1);
	vector<double> hh_data(Close_data.size(), 0);
	data_length = Close_data.size() - channel_length;
	for (int channel_start = 17000 - channel_length; channel_start < data_length; channel_start++) {
		channel_end = channel_start + channel_length-1;
		if (hh > High_data[channel_start - 1]) {
			hh = max(hh, High_data[channel_end]);
		
		}
		else {
			hh = *max_element(High_data.begin() + channel_start, High_data.begin() + channel_end + 1);
		}
		hh_data[channel_end + 1] = hh;
	}
	return hh_data;
}
vector<double> llf(int channel_length, vector<double>& Open_data, vector<double>& Close_data, vector<double>& High_data, vector<double>& Low_data) {
	double ll;
	int channel_start, channel_end,data_length;
	ll = *min_element(Low_data.begin() + 17000 - channel_length, Low_data.begin() + 17000 + 1);
	vector<double> ll_data(Close_data.size(), 0);
	data_length = Close_data.size() - channel_length;
	for (int channel_start = 17000 - channel_length; channel_start < data_length; channel_start++) {
		channel_end = channel_start + channel_length-1;
		if (ll < Low_data[channel_start - 1]) {
			ll = min(ll, Low_data[channel_end]);

		}
		else {
			ll = *min_element(Low_data.begin() + channel_start, Low_data.begin() + channel_end + 1);
		}
		ll_data[channel_end + 1] = ll;
	}
	return ll_data;
}
int main() {
	vector<double> Open_data,High_data,Low_data,Close_data,hh_data,ll_data;
	//readfile
	fstream file;
	file.open("HO.csv");
	int i,channel_length_new;
	string line;
	double k,k_new=0,stop_percentage_new;
	getline(file, line, '\n');
		while (getline(file, line, '\n'))  //讀檔讀到跳行字元
		{
			istringstream templine(line); // string 轉換成 stream
			string data;
			i = 0;
			while (getline(templine, data, ',')) //讀檔讀到逗號
			{
				if (i == 3) Open_data.push_back(atof(data.c_str()));
				if (i == 4) High_data.push_back(atof(data.c_str()));
				if (i == 5) Low_data.push_back(atof(data.c_str()));
				if (i == 6) Close_data.push_back(atof(data.c_str()));
				i++;
			}
		}
	file.close();
	long beginTime = clock();
	for (int channel_length = 100; channel_length <= 10000;channel_length=channel_length+10) {
		hh_data = hhf(channel_length, Open_data, Close_data, High_data, Low_data);
		ll_data = llf(channel_length, Open_data, Close_data, High_data, Low_data);
		// experiment
		//k_new = trading(hh_data, ll_data, 100, .005, Open_data, Close_data, High_data, Low_data); // initial data point
		// end experiment
		for (double j = 0.005; j <= 0.1; j = j + 0.001) {
			k = trading(hh_data, ll_data, channel_length, j, Open_data, Close_data, High_data, Low_data);
			if (k_new <= k) {
				k_new = k;
				stop_percentage_new = j;
				channel_length_new = channel_length;
			}
		}
	}
	long endTime = clock();
	/*hh_data = hhf(1000, Open_data, Close_data, High_data, Low_data);
	ll_data = llf(1000, Open_data, Close_data, High_data, Low_data);
	k = trading(hh_data, ll_data, 1000, 0.011, Open_data, Close_data, High_data, Low_data);
	cout << (double) (endTime - beginTime)/CLOCKS_PER_SEC << endl;*/
	cout << "Grid optimal stop: " << stop_percentage_new << " Grid optimal length: " << channel_length_new <<" Grid optimal RoA: "<<k_new<< endl;
	//system("pause");
	cout << "Grid time: " << (endTime - beginTime) << endl;
	sim_annealing(1, .001,10000, Open_data, Close_data, High_data, Low_data);    ofstream test;
	return 0;
}

double alpha(double temperature){
	return(temperature * .995);
}

double probability(double temperature, double RoA, double RoA_neighbor)
{
	double prob = exp(-(RoA - RoA_neighbor)/temperature); // Boltzmann 
	return(prob);
}

void sim_annealing(double temperature, double temperature_min, int k,vector<double>Open_data,vector<double>& Close_data,
	vector<double>& High_data,vector<double>& Low_data)
{
	long start_time = clock();


	vector<double> hh_data;
	vector<double> ll_data;

	int accept = 0;
	int reject = 0;
	int accept_worse = 0;
	// seed random number generator
	srand(time(NULL));

	// Generate first random solution
	//rand attribution: http://www.dreamincode.net/forums/topic/14057-producing-random-numbers/
	int old_channel_length = int(rand() % 1980)*5;
	cout << "Original channel length: " << old_channel_length << endl;
	double old_stop_percentage = double(rand() % int(1000*MAX_STOP) + int(1000*MIN_STOP))/1000;
	cout << "Original stop percentage: " << old_stop_percentage << endl;

	hh_data = hhf(old_channel_length, Open_data, Close_data, High_data, Low_data);
	ll_data = llf(old_channel_length, Open_data, Close_data, High_data, Low_data);


	double old_RoA = trading(hh_data, ll_data, old_channel_length, old_stop_percentage,
		Open_data, Close_data, High_data, Low_data); 

	int new_channel_length;
	double new_stop_percentage;

	double original_RoA = old_RoA;


	while(temperature > temperature_min)
	{
		// Generate random neighbor with k iterations
		for(int i=0; i < k; i++)
		{
			int random = rand() % 10 + 1; // generate random number between 1 and 10
			//cout << "Random number generated for channel: " << random << endl;
			/// only move one variable at a time
			if(random > 5){
				random = random = rand() % 10 + 1;
				if(random > 5)
					new_channel_length = old_channel_length + (int(100*temperature)/5)*CHANNEL_INCREMENT;
				else
					new_channel_length = old_channel_length - (int(100*temperature)/5)*CHANNEL_INCREMENT;
			}else{
				random = rand() % 10 + 1;
				if(random > 5)
					new_stop_percentage = old_stop_percentage + 100*temperature*STOP_INCREMENT;
				else
					new_stop_percentage = old_stop_percentage - 100*temperature*STOP_INCREMENT;
			}

		}
		if(new_channel_length < MIN_CHANNEL)
			new_channel_length = MIN_CHANNEL;
		if(new_channel_length > MAX_CHANNEL)
			new_channel_length = MAX_CHANNEL;
		if(new_stop_percentage < MIN_STOP)
			new_stop_percentage = MIN_STOP;
		if(new_stop_percentage > MAX_STOP)
			new_stop_percentage = MAX_STOP;

		hh_data = hhf(new_channel_length, Open_data, Close_data, High_data, Low_data);
		ll_data = llf(new_channel_length, Open_data, Close_data, High_data, Low_data);

		double new_RoA = trading(hh_data, ll_data, new_channel_length, new_stop_percentage,
		Open_data, Close_data, High_data, Low_data); 
		//cout << "Old RoA: " << old_RoA << "New RoA: " << new_RoA <<endl;

		if(old_RoA > new_RoA)
		{
			// old solution was better
			// maybe go to new solution
			double random_for_checking = double(rand() % 99 + 0)/100;
			//cout << "Random number generated to test against probability: " << random_for_checking << endl;
			double prob_move = probability(temperature,old_RoA,new_RoA);
			//cout << "Probability: " << prob_move << endl;
			if(prob_move >= random_for_checking)
			{
				// go to new solution anyways
				old_channel_length = new_channel_length;
				old_stop_percentage = new_stop_percentage;
				old_RoA = new_RoA;
				accept++;
				accept_worse++;
			}
			// else, do not go to new solution -- keep old solution.
			reject++;
		}
		else 
		{
			// always accept better solution
			old_channel_length = new_channel_length;
			old_stop_percentage = new_stop_percentage;
			old_RoA = new_RoA;
			accept++;
		}


		temperature = alpha(temperature);

	}
	long end_time = clock();

	cout << "Sim anneal optimal RoA: " << old_RoA << endl;
	cout << "Sim anneal optimal channel length: " << old_channel_length << endl;
	cout << "Sim anneal optimal stop percentage: " << old_stop_percentage << endl;
	cout << "First solution generated: " << original_RoA << ". Optimized: " << old_RoA << endl;
	cout << "Simulated annealing time: " << (end_time - start_time) << endl;

	return;
}

