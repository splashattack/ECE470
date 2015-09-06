//* Object Oriented City Simulator - Homework 2 *


/*
* HW2
* 9/3/15
* Caleb Gill
*/
#include <iostream>
#include <iomanip>
using namespace std;

class CITY {
private:
    double urban, suburban, exurban;    // current populations
    bool   grow;                        // true if the total city population grew last year

    /*         URBAN SUBURBAN EXURBAN
    URBAN       1.1    0.3      0.7
    SUBURBAN    0.1    1.2      0.3
    EXURBAN     0.2    0.6      1.3
    */
    const double UtoU = .011, UtoS = .003, UtoE = .007, // %pop change in urban areas
                 StoS = .012, StoU = .001, StoE = .003, // %pop change in suburban areas
                 EtoE = .013, EtoU = .002, EtoS = .006; // %pop change in exurban areas
public:
    
    CITY(double urb, double sub, double exu)
    // sets urban to u, suburban to s, exurban to x, grow to true
    {
        urban = urb;
        suburban = sub;
        exurban = exu;
        grow = true;
    }

    // returns true if at least one of the population variables is non-zero
    bool isAlive() const { return (urban || suburban || exurban != 0) ? true : false; }

    // returns the state of the grow variable
    bool hasBeenGrowing() const { return grow; }

    void ComputeNextYear()
    {
        
        //  Replaces the old values with the new ones. 
        double urban_old = urban;
        double suburban_old = suburban;
        double exurban_old = exurban;

        //  Calculates the new values of urban, suburban and exurban.
        urban += (urban_old * UtoU) + (suburban_old * StoU) + (exurban_old * EtoU);
        suburban -= suburban_old * StoU;
        exurban -= exurban_old * EtoU;

        suburban += (suburban_old * StoS) + (urban_old * UtoS) + (exurban_old * EtoS);
        urban -= (urban_old * UtoS);
        exurban -= (exurban_old * EtoS);

        exurban += (exurban_old * EtoE) + (urban_old * UtoE) + (suburban_old * StoE);
        urban -= (urban_old * UtoE);
        suburban -= (suburban_old * StoE);

        //  Update the grow variable here by comparing the sum of old 
        //  with the sum of new populations.
        grow = ((urban_old + suburban_old + exurban_old) <= (urban + suburban + exurban)) ? true : false;      
       
    }
    void PrintAnnualReport(ostream& out) const
    {
        out <<  setw(8) << urban << setw(8) << suburban << setw(8) << exurban;
    }
}; /* CITY Class version: 2010F-12S */



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
