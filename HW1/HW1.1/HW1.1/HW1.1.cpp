/**
* @course ECEx70
* @homework 1.1 (Heat Index Calculator)
* @author Caleb Gill
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double conv_Celsius_to_Farenheit(double c);
double conv_Farenheit_to_Celsius(double f);
double comp_HeatIndex_inFarenheit(double tempFar, double relHum);

int main() {

	double temp;
	double humid;
	cout << "Please specify the temperature and humidity" << endl;
	cout << "T (F) = "; cin >> temp;
	cout << "H (%) = "; cin >> humid;

	double wchl = comp_HeatIndex_inFarenheit(temp, humid);

	cout << showpoint << fixed << setprecision(1);
	cout << "The temperature   is " << temp << "F, i.e. " << conv_Farenheit_to_Celsius(temp) << "C." << endl;
	cout << "Heat index factor is " << wchl << "F, i.e. " << conv_Farenheit_to_Celsius(wchl) << "C." << endl;
	return(0);
}

// converts temperature from Fahrenheit into Celsius
double conv_Farenheit_to_Celsius(double f) {
	double c = (f - 32) * 5 / 9;
	return(c);
}

// calculates WindChill index for given temperature in F and wind speed in mph
double comp_HeatIndex_inFarenheit(double tempFar, double relHum) {
	const double c1 = -42.38, c2 = 2.049, c3 = 10.14, c4 = -0.2248, c5 = -6.838E-3, c6 = -5.482E-2, c7 = 1.228E-3, c8 = 8.528E-4, c9 = -1.99E-6;
	double T = tempFar;
	double R = relHum;
	double index = c1 + (c2 * T) + (c3 * R) + (c4 * T * R) + (c5 * pow(T,2)) + (c6 * pow(R,2)) + (c7 * pow(T,2) * R) +
				   (c8 * T * pow(R,2)) + (c9 * pow(T,2) * pow(R, 2));
	return(index);
}
