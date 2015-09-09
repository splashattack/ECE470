//* Object Oriented City Simulator - Homework 2 *


/*
* HW2
* 9/3/15
* Caleb Gill
*/
#include <iostream>
#include <iomanip>

#include "city.h"
using namespace std;



   //* Do not modify content below, it goes to program.cpp file *


int main() {
    double Urban, Suburban, eXurban;

    cout << "Please enter the initial populations for Peoria (PIA)\nEnter in thousands (U,S,X) ";
    cin >> Urban >> Suburban >> eXurban;
    CITY Peoria(Urban, Suburban, eXurban);

    cout << "Please enter the initial populations for Bloomington-Normal (BMI)\nEnter in thousands (U,S,X) ";
    cin >> Urban >> Suburban >> eXurban;
    CITY BloomingtonNormal(Urban, Suburban, eXurban);

    unsigned years;
    cout << "How many years to simulate? ";
    cin >> years;


    cout << showpoint << fixed << setprecision(2);
    for (unsigned y = 1; y <= years; y++) {

        Peoria.ComputeNextYear();
        BloomingtonNormal.ComputeNextYear();

        if (y % 5 == 0) {
            cout << setw(3) << y << "  PIA: ";
            if (Peoria.hasBeenGrowing()) cout << "+"; else cout << "-";
            Peoria.PrintAnnualReport(cout);             // do continue printing the report in the same line
            cout << "  BMI: ";
            if (BloomingtonNormal.hasBeenGrowing()) cout << "+"; else cout << "-";
            BloomingtonNormal.PrintAnnualReport(cout);  // do continue printing the report in the same line
            cout << endl;                               // now we end the line
        }
        if (!Peoria.isAlive() && BloomingtonNormal.isAlive()) break;
    }

    if (years % 5 != 0) {
        cout << "The final populations are: " << endl;
        cout << setw(3) << years << "  PIA: ";
        if (Peoria.hasBeenGrowing()) cout << "+"; else cout << "-";
        Peoria.PrintAnnualReport(cout);
        cout << "  BMI: ";
        if (BloomingtonNormal.hasBeenGrowing()) cout << "+"; else cout << "-";
        BloomingtonNormal.PrintAnnualReport(cout);
        cout << endl;
    }
    else {
        cout << "The final populations are listed above." << endl;
    }

    if (!Peoria.isAlive()) cout << "I am sorry to report but the city of Peoria died out :-(" << endl;
    if (!BloomingtonNormal.isAlive()) cout << "I am sorry to report but the city of Bloomington-Normal died out :-(" << endl;

    return(0);
}
