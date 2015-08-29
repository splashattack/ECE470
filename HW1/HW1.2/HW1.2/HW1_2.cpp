/**
* @course ECE470
* @homework 1.2
* @author Caleb Gill
*/
#include <stdint.h>
#include <iostream>

using namespace std;
/*
           URBAN SUBURBAN EXURBAN
URBAN       1.1    0.3      0.7
SUBURBAN    0.1    1.2      0.3
EXURBAN     0.2    0.6      1.3
*/



int main()
{
	double urbanPop = 2100000;
	double suburbanPop = 1400000;
	double exurbanPop = 900000;

    cout << "Year: 0" << endl;
    cout << "Urban Popuation: " << (int)urbanPop << endl;
    cout << "Suburban Population: " << (int)suburbanPop << endl;
    cout << "Exurban Population: " << (int)exurbanPop << endl;
    cout << "-----------------------------------------" << endl;


    for (uint8_t year = 1; year < 51; year++)
    {
        double urbanPop_old = urbanPop;
        double suburbanPop_old = suburbanPop;
        double exurbanPop_old = exurbanPop;

        urbanPop += (suburbanPop_old * 0.001) + (exurbanPop_old * 0.002);
        suburbanPop -= suburbanPop_old * 0.001;
        exurbanPop -= exurbanPop_old * 0.002;

        suburbanPop += (urbanPop_old * 0.003) + (exurbanPop_old * 0.006);
        urbanPop -= (urbanPop_old * 0.003);
        exurbanPop -= (exurbanPop_old * 0.006);

        exurbanPop += (urbanPop_old * 0.007) + (suburbanPop_old * 0.003);
        urbanPop -= (urbanPop_old * 0.007);
        suburbanPop -= (suburbanPop_old * 0.003);

        if (year % 10 == 0)
        {
            cout << "Year: " << (int)year << endl;
            cout << "Urban Popuation: " << (int)urbanPop << endl;
            cout << "Suburban Population: " << (int)suburbanPop << endl;
            cout << "Exurban Population: " << (int)exurbanPop << endl;
            cout << "-----------------------------------------" << endl;
        }
    }
}