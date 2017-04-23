#include <iostream>
#include <cmath>

using namespace std;

int main() {
	//set some constants, which represent the seconds in a year, the seconds in a day, etc.
	const int SECONDS_YEARS = 31536000, SECONDS_DAYS = 86400, SECONDS_HOURS = 3600, SECONDS_MINUTES = 60;
	double speed, time, distance, left_seconds;
	int years, days, hours, minutes, seconds;

	//input the time of travel
	cout << "Please give me the time of travel in seconds. ";
	cin >> time;

	//input the speed of travel
	cout << "Please give me your speed in miles per hour. ";
	cin >> speed;

	//convert seconds into years,days,hours,minutes and seconds. "left_seconds" represents the seconds left after every round's conversion.
	years = time / SECONDS_YEARS;
	left_seconds = time - years*SECONDS_YEARS;
	days = left_seconds / SECONDS_DAYS;
	left_seconds = left_seconds - days*SECONDS_DAYS;
	hours = left_seconds / SECONDS_HOURS;
	left_seconds = left_seconds - hours*SECONDS_HOURS;
	minutes = left_seconds / SECONDS_MINUTES;
	left_seconds = left_seconds - minutes*SECONDS_MINUTES;
	seconds = left_seconds;

	//output the time in a new measurement
	cout << "You have been traveling for: " << years << " years " << days << " days " << hours << " hours " << minutes << " minutes " << seconds << " seconds " << endl;

	//calculate the distance traveled
	distance = time*speed / SECONDS_HOURS;
	cout << "Your distance traveled is: " << distance << " miles." << endl;

	system("pause");
	return 0;
}
