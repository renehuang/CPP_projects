#include <iostream>//author Wang, Jiakang
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <time.h>

using namespace std;

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
				current = current + 1000 * (Close_data[channel_end + 1] - Open) - 9.5;
				flg = 0;
			}
			else if (High >= hh) {
				entry_price = hh;
				//cout << hh << " " << channel_end << endl;
				market_position = 1;
				prev_peak = hh;
				buy = buy + 1;
				current = current + 1000 * (Close_data[channel_end + 1] - hh) - 9.5;
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
				current = current - 1000 * (Close_data[channel_end + 1] - Open) - 9.5;
				flg = 0;
			}
			else if (Low <= ll) {
				entry_price = ll;
				//cout << -ll << " " << channel_end << endl;
				market_position = -1;
				prev_trough = ll;
				sell = sell + 1;
				current = current - 1000 * (Close_data[channel_end + 1] - ll) - 9.5;
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
				current = current + 1000 * (deal_price - Close) - 9.5;
				//cout << "**" << deal_price << " " << channel_end<<endl;
			}
			else if (Low <= prev_peak*(1 - stop_percentage)) {
				deal_price = prev_peak*(1 - stop_percentage);
				market_position = 0;
				current = current + 1000 * (deal_price - Close) - 9.5;
				//cout << "**" << deal_price << " " << channel_end<<endl;
			}
			else {
				current = current + 1000 * (Close_data[channel_end + 1] - Close);
			}
		}

		if (market_position < 0) {
			if (Close < prev_trough) {
				prev_trough = Close;
			}
			if (Open >= prev_trough*(1 + stop_percentage)) {
				deal_price = Open;
				market_position = 0;
				current = current - 1000 * (deal_price - Close) - 9.5;
				//cout << "**" << deal_price << " " << channel_end<<endl;
			}
			else if (High >= prev_trough*(1 + stop_percentage)) {
				deal_price = prev_trough*(1 + stop_percentage);
				market_position = 0;					
				current = current - 1000 * (deal_price - Close) - 9.5;
				//cout << "**" << deal_price << " " << channel_end<<endl;
			}
			else {
				current = current - 1000 * (Close_data[channel_end + 1] - Close);
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
	vector<double> Open_wdata,High_wdata,Low_wdata,Close_wdata,hh_data,ll_data,Open_data,High_data,Low_data,Close_data;
	//readfile
	fstream file;
	file.open("TY.csv");
	int i,channel_length_new;
	string line;
	double k,k_new=0,stop_percentage_new;
	getline(file, line, '\n');
		while (getline(file, line, '\n'))  //
		{
			istringstream templine(line); // 
			string data;
			i = 0;
			while (getline(templine, data, ',')) //
			{
				if (i == 2) Open_wdata.push_back(atof(data.c_str()));
				if (i == 3) High_wdata.push_back(atof(data.c_str()));
				if (i == 4) Low_wdata.push_back(atof(data.c_str()));
				if (i == 5) Close_wdata.push_back(atof(data.c_str()));
				i++;
			}
		}
	file.close();
	int total_data = Close_wdata.size();
	//cout << total_data<<endl;
	//total_data = (Close_wdata.size()-10*252*72-72*21*3);
	/*CHANGE HERE*/
	total_data = (Close_wdata.size()-4*252*72-72*21*3);
	//total_data = (Close_wdata.size()-4*252*72-72*21*6);
	//total_data = (Close_wdata.size()-10*252*72-72*21*6);
	long beginTime = clock();

	FILE *output;
	//output = fopen("GridSearchOutput_TY_T10_tau1.csv", "w");
	/*CHANGE HERE*/
	output = fopen("GridSearchOutput_TY_T4_tau1_new.csv", "w");
	//output = fopen("GridSearchOutput_TY_T4_tau2.csv", "w");
	//output = fopen("GridSearchOutput_TY_T10_tau2.csv", "w");

	//for (int data_start = 0,data_slide=10*252*72; data_start <= total_data; k_new=0,data_start = data_start + 72*21*3, data_slide=data_slide+72*21*3) {
	/*CHANGE HERE*/
	for (int data_start = 0,data_slide=4*252*3; data_start <= total_data; k_new=0,data_start = data_start + 72*21*3, data_slide=data_slide+72*21*3) {
	//for (int data_start = 0,data_slide=4*252*72; data_start <= total_data; k_new=0,data_start = data_start + 72*21*6, data_slide=data_slide+72*21*6) {
	//for (int data_start = 0,data_slide=10*252*72; data_start <= total_data; k_new=0,data_start = data_start + 72*21*6, data_slide=data_slide+72*21*6) {

		Open_data.assign(Open_wdata.begin() + data_start, Open_wdata.begin() + data_slide);
		High_data.assign(High_wdata.begin() + data_start, High_wdata.begin() + data_slide);
		Low_data.assign(Low_wdata.begin() + data_start, Low_wdata.begin() + data_slide);
		Close_data.assign(Close_wdata.begin() + data_start, Close_wdata.begin() + data_slide);
		//cout << Open_data[1] <<" "<< High_data[1]<<" " << Low_data[1] <<" "<< Close_data[1]<<endl;
		//system("pause");
		for (int channel_length = 5000; channel_length <= 16000; channel_length = channel_length + 20) {
			hh_data = hhf(channel_length, Open_data, Close_data, High_data, Low_data);
			ll_data = llf(channel_length, Open_data, Close_data, High_data, Low_data);
			for (double j = 0.05; j <= 0.2; j = j + 0.002) {
				k = trading(hh_data, ll_data, channel_length, j, Open_data, Close_data, High_data, Low_data);
				if (k_new <= k) {
					k_new = k;
					stop_percentage_new = j;
					channel_length_new = channel_length;
				}
			}
		}
		cout << stop_percentage_new << " " << channel_length_new << " " << k_new << endl;
		fprintf(output, "%lf, %d, %lf\n", stop_percentage_new, channel_length_new, k_new);

		Open_data.clear();
		High_data.clear();
		Low_data.clear();
		Close_data.clear();
		hh_data.clear();
		ll_data.clear();


		// fprintf(output, "%lf,%lf,%lf\n", stop_percentage_new, channel_length_new, k_new);
		
	}

	fclose(output);


	long endTime = clock();
	/*hh_data = hhf(1000, Open_data, Close_data, High_data, Low_data);
	ll_data = llf(1000, Open_data, Close_data, High_data, Low_data);
	k = trading(hh_data, ll_data, 1000, 0.011, Open_data, Close_data, High_data, Low_data);*/
	cout << (double) (endTime - beginTime)/CLOCKS_PER_SEC << endl;
	//cout << stop_percentage_new << " " << channel_length_new <<" "<<k_new<< endl;
	system("pause");
	return 0;
}