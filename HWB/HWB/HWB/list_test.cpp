//* A small program that tests thoroughly our simplified list *


#include "list.h"
#include <iostream>
using namespace std;

#ifdef _MSC_VER
// Microsoft compiler specific memory leak detection tool
#include <crtdbg.h>
#endif

// this function prints contents of a list without duplicating
template <typename D> void PRINTREF(const list<D> &c) {
    cout << "L: ";
    list<D>::const_iterator it;
    for (it = c.begin(); it != c.end(); ++it)
        cout << " " << *it;
    cout << endl;
}

// this function prints contents of a list in reverse without duplicating
template <typename D> void PRINTREV(const list<D> &c) {
    cout << "L: ";
    list<D>::const_reverse_iterator it;
    for (it = c.rbegin(); it != c.rend(); ++it)
        cout << " " << *it;
    cout << endl;
}

// this function prints contents of a copy of the actual list
template <typename D> void PRINTVAL(list<D> c) {
    cout << "L: ";
    list<D>::iterator it;
    for (it = c.begin(); it != c.end(); ++it)
        cout << " " << *it;
    cout << endl;
}


int main() {
    {
        list<int>                   L, C;
        list<int>::iterator         S;
        list<int>::const_iterator   T;
        int                         i;


        cout << "Testing push_back and push_front..." << endl;
        for (i = 0; i<5; i++) {
            L.push_back(i); // <-- THIS IS A HW FEATURE
            L.push_front(i);
        }
        cout << "Each PRINT will also test ++const_iterator..." << endl;
        PRINTREF(L);
        cout << "Done, verify the results" << endl << endl;

        cout << "Testing size... " << L.size() << " - Done, check if correct" << endl << endl;


        cout << "Testing the copy constructor - passing..." << endl;
        PRINTVAL(L);  // <-- THIS IS A HW FEATURE
        cout << "Testing the copy constructor - correct passing..." << endl;
        PRINTREF(L);
        cout << "Done, verify the results" << endl << endl;


        cout << "Testing pop_back and pop_front..." << endl;
        for (i = 0; i<2; i++) {
            L.pop_back(); // <-- THIS IS A HW FEATURE
            L.pop_front();
        }
        PRINTREF(L);
        cout << "Done, verify the results" << endl << endl;


        cout << "Testing insert at the begin, inside and at the end..." << endl;
        i = -1; L.insert(L.begin(), i);
        S = L.begin(); ++S; i = -2; L.insert(S, i);
        i = -3; L.insert(L.end(), i);
        PRINTREF(L);
        cout << "Done, verify the results" << endl << endl;


        cout << "Testing erase..." << endl;
        S = L.begin(); ++S; L.erase(S);
        PRINTREF(L);
        cout << "Done, verify the results" << endl << endl;


        cout << "Testing ++const_reverse_iterator..." << endl;
        PRINTREV(L);
        cout << "Done, verify the results" << endl << endl;


        cout << "Testing removing until empty..." << endl;
        while (!L.empty()) L.pop_front();
        PRINTREF(L);
        cout << "Done, verify the results" << endl << endl;


        cout << "Testing size... " << L.size() << " - Done, check if correct" << endl << endl;


        cout << "Regenerating the list for more tests..." << endl;
        for (i = 1; i <= 10; i++) {
            L.push_front(i);
        }
        PRINTREF(L);


        cout << "Testing iterator ++ and -- ..." << endl;
        cout << "Testing pre ++/-- We will print positions: 2nd, 3rd and 2nd ..." << endl;
        S = L.begin();
        ++S; cout << " " << *S;
        ++S; cout << " " << *S;
        --S; cout << " " << *S; // <-- THIS IS A HW FEATURE
        cout << endl;
        cout << "Testing pos ++/-- We will print positions: 2nd, 3rd and 2nd ..." << endl;
        S = L.begin();
        S++; cout << " " << *S;
        S++; cout << " " << *S;
        S--; cout << " " << *S; // <-- THIS IS A HW FEATURE
        cout << endl;
        cout << "Done, verify the results" << endl << endl;


        cout << "Testing pre ++ We will print the first position ..." << endl;
        S = L.end(); ++S; cout << " " << *S << endl;
        cout << "Testing pre -- We will print the last position ..." << endl;
        S=L.end(); --S; cout << " " << *S << endl; // <-- THIS IS A HW FEATURE
        cout << "Testing pos ++ We will print the first position ..." << endl;
        S = L.end(); S++; cout << " " << *S << endl;
        cout << "Testing pos -- We will print the last position ..." << endl;
        S=L.end(); S--; cout << " " << *S << endl; // <-- THIS IS A HW FEATURE
        cout << "Done, verify the results" << endl << endl;


        cout << "Testing const_iterator ++ and -- ..." << endl;
        cout << "Testing const pre ++ We will print the first position ..." << endl;
        T = L.end(); ++T; cout << " " << *T << endl;
        cout << "Testing const pre -- We will print the last position ..." << endl;
        T=L.end(); --T; cout << " " << *T << endl; // <-- THIS IS A HW FEATURE
        cout << "Testing const pos ++ We will print the first position ..." << endl;
        T = L.end(); T++; cout << " " << *T << endl;
        cout << "Testing const pos -- We will print the last position ..." << endl;
        T=L.end(); T--; cout << " " << *T << endl; // <-- THIS IS A HW FEATURE
        cout << "Done, verify the results" << endl << endl;


        cout << "Creating another list for insert collection test..." << endl;
        for (i = 1; i <= 3; i++) {
            C.push_front(i);
        }
        PRINTREF(L);
        cout << "Testing insert collection at the second position ..." << endl;
        S = L.begin(); S++;
        L.insert(S, C.begin(), C.end());
        PRINTREF(L);
        cout << "Done, verify the results" << endl << endl;


        // Testing disabling assignment operator ...
        // C=L; // <-- THIS IS A HW FEATURE - should not compile and/or cause linking error
        // if you do not disable or implement it the program crashes at the end when destructors are called

    }

#ifdef _MSC_VER
    if (_CrtDumpMemoryLeaks())
        cerr << "Memory leaks occurred!" << endl;
    else    cerr << "No memory leaks detected!" << endl;
#else
    cerr << "Memory leaks detection unavailable!" << endl;
#endif

    return(0);
}
