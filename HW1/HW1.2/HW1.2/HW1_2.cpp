/**
* @course ECE470
* @homework 1.2
* @author Caleb Gill
*/
#include <cstdint>
#include <iostream>
#include <cmath>

using namespace std;
/*
           URBAN SUBURBAN EXURBAN
URBAN       1.1    0.3      0.7
SUBURBAN    0.1    1.2      0.3
EXURBAN     0.2    0.6      1.3
*/
const double UtoU = .011, UtoS = .003, UtoE = .007, // %pop change in urban areas
             StoS = .012, StoU = .001, StoE = .003, // %pop change in suburban areas
             EtoE = .013, EtoU = .002, EtoS = .006; // %pop change in exurban areas

int main()
{
    unsigned int maxYear;
	double urbanPop, suburbanPop, exurbanPop;

    //User input
    cout << "Enter the number of years to calculate population for: "; cin >> maxYear;
    cout << "Starting Urban Popuation (in Millions): "; cin >> urbanPop;
    cout << "Starting Suburban Population (in Millions): ";  cin >> suburbanPop;
    cout << "Starting Exurban Population (in Millions): "; cin >> exurbanPop;
    cout << "-----------------------------------------" << endl;

    //Scale from millions to ones
    urbanPop *= pow(10, 6);
    suburbanPop *= pow(10, 6);
    exurbanPop *= pow(10, 6);

    for (unsigned int currentYear = 1; currentYear <= maxYear; currentYear++)
    {
        double urbanPop_old = urbanPop;
        double suburbanPop_old = suburbanPop;
        double exurbanPop_old = exurbanPop;

        urbanPop += (urbanPop_old * UtoU) + (suburbanPop_old * StoU) + (exurbanPop_old * EtoU);
        suburbanPop -= suburbanPop_old * StoU;
        exurbanPop -= exurbanPop_old * EtoU;

        suburbanPop += (suburbanPop_old * StoS) + (urbanPop_old * UtoS) + (exurbanPop_old * EtoS);
        urbanPop -= (urbanPop_old * UtoS);
        exurbanPop -= (exurbanPop_old * EtoS);

        exurbanPop += (exurbanPop_old * EtoE) + (urbanPop_old * UtoE) + (suburbanPop_old * StoE);
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
    system("pause");
    return 0;
}