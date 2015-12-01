//* Test program for long term and short term moving averages RotaryBuffers *


// @version 2.0 (Fall 2015)
// Note: This program is allegedly correct, do not modify it
//       If you suspect an error, consult the instructor (to get it corrected and be awarded an extra credit)
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#include "rbuffer.h"

int main()
{
    RotaryBuffer<int, 8, 3> radon;
    ofstream   clog("moving_RotaryBuffer_test_log.txt");

    cout << "Enter subsequent sensor readings >=0, -1 to reset, -2 to shut down" << endl;
    for (;;)
    {
        int data; cout << "> "; cin >> data;
        clog << " > " << data << endl;
        if (data == -1) {
            radon.clear();
            if (radon.ready()) {
                cout << "Failed to purge data\a!" << endl;
                clog << "Failed to purge data\a!" << endl;
            }
            else {
                cout << "All data purged!" << endl;
                clog << "All data purged!" << endl;
            }
            continue;
        }
        else {
            if (data<0) break;
        }

        radon.store(data);
        if (radon.ready())
        {
            int sh = radon.ShortAverage();
            int lg = radon.LongAverage();
            cout << "S:" << setw(3) << sh << " L:" << setw(3) << lg << endl;
            clog << "S:" << setw(3) << sh << " L:" << setw(3) << lg << endl;
            if (lg>4.0) cout << "\a";
        }
    }

    radon.clear();
    if (radon.ready()) {
        cout << "Warning: privacy violated, data RotaryBuffer has not been purged\a!" << endl;
        clog << "Warning: privacy violated, data RotaryBuffer has not been purged\a!" << endl;
    }
    else {
        cout << "The device is ready to be shut down." << endl;
        clog << "The device is ready to be shut down." << endl;
    }
    clog.close();
    return(0);
}
