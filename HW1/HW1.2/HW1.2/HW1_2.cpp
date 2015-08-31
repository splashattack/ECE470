/**
* @course ECE470
* @homework 1.2
* @author Caleb Gill
*/
#include <stdint.h>
#include <iostream>
#include <cmath>

using namespace std;
/*
           URBAN SUBURBAN EXURBAN
URBAN       1.1    0.3      0.7
SUBURBAN    0.1    1.2      0.3
EXURBAN     0.2    0.6      1.3
*/
const double UtoS = .003, UtoE = .007, // %pop moving from Urban to Sub/Exurban areas
             StoU = .001, StoE = .003, // %pop moving from Suburban to (Ex)urban areas
             EtoU = .002, EtoS = .006; // %pop moving from Exurban to (Sub)urban areas

int main()
{
    uint16_t maxYear;
	double urbanPop, suburbanPop, exurbanPop;

    //User input
    cout << "Enter the number of years to calculate population for: "; cin >> maxYear;
    cout << "Starting Urban Popuation (in Millions): "; cin >> urbanPop;
    cout << "Starting Suburban Population(in Millions): ";  cin >> suburbanPop;
    cout << "Starting Exurban Population(in Millions): "; cin >> exurbanPop;
    cout << "-----------------------------------------" << endl;

    //Scale from millions to ones
    urbanPop *= pow(10, 6);
    suburbanPop *= pow(10, 6);
    exurbanPop *= pow(10, 6);

    for (int currentYear = 1; currentYear <= maxYear; currentYear++)
    {
        double urbanPop_old = urbanPop;
        double suburbanPop_old = suburbanPop;
        double exurbanPop_old = exurbanPop;

        urbanPop += (suburbanPop_old * StoU) + (exurbanPop_old * EtoU);
        suburbanPop -= suburbanPop_old * StoU;
        exurbanPop -= exurbanPop_old * EtoU;

        suburbanPop += (urbanPop_old * UtoS) + (exurbanPop_old * EtoS);
        urbanPop -= (urbanPop_old * UtoS);
        exurbanPop -= (exurbanPop_old * EtoS);

        exurbanPop += (urbanPop_old * UtoE) + (suburbanPop_old * StoE);
        urbanPop -= (urbanPop_old * UtoE);
        suburbanPop -= (suburbanPop_old * StoE);

        if (currentYear % 10 == 0)
        {
            cout << "Year: " << currentYear << endl;
            cout << "Urban Popuation: " << (int)urbanPop << endl;
            cout << "Suburban Population: " << (int)suburbanPop << endl;
            cout << "Exurban Population: " << (int)exurbanPop << endl;
            cout << "-----------------------------------------" << endl;
        }
    }
}