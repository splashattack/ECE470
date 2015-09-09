#include "city.h"


CITY::CITY(double urb, double sub, double exu) : urban(urb), suburban(sub), exurban(exu), grow(true)
{
    UtoU = .011;
    UtoS = .003;
    UtoE = .007;
    // %pop change in urban areas
    StoS = .012;
    StoU = .001;
    StoE = .003;
    // %pop change in suburban areas
    EtoE = .013;
    EtoU = .002;
    EtoS = .006;
    // %pop change in exurban areas
};

bool CITY::hasBeenGrowing() const
{
    return grow; 
}

void CITY::ComputeNextYear()
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
    grow = ((urban_old + suburban_old + exurban_old) < (urban + suburban + exurban));

}

void CITY::PrintAnnualReport(ostream& out) const 
{
    out << setw(8) << urban << setw(8) << suburban << setw(8) << exurban; 
}
