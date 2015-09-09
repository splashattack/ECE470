#pragma once

using namespace std;

#include <iomanip>


class CITY {
private:
    double urban, suburban, exurban;    // current populations
    bool   grow;                        // true if the total city population grew last year

                                        /*         URBAN SUBURBAN EXURBAN
                                        URBAN       1.1    0.3      0.7
                                        SUBURBAN    0.1    1.2      0.3
                                        EXURBAN     0.2    0.6      1.3
                                        */
    double UtoU, UtoS, UtoE, // %pop change in urban areas
                  StoS, StoU, StoE, // %pop change in suburban areas
                  EtoE, EtoU, EtoS; // %pop change in exurban areas
public:

    CITY(double urb, double sub, double exu);
    // sets urban to u, suburban to s, exurban to x, grow to true

    // returns true if at least one of the population variables is non-zero
    bool isAlive() const { return (urban + suburban + exurban != 0); }

    // returns the state of the grow variable
    bool hasBeenGrowing() const;

    void ComputeNextYear();

    void PrintAnnualReport(ostream& out) const;
}; /* CITY Class version: 2010F-12S */
