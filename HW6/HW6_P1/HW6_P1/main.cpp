//* HW 5 - correct the faulty BadVector class with 4 errors *


/*
* INSERT YOUR HW HEADER HERE
*/
/**
Note1: You CAN change only the definition and implementation
of the BadVector class. You MUST NOT change the test program
or the additional test function.

Note2: Some compilers produce code that does not crash despite
apparent memory access violations.

Note3: The FOUR errors planted in this file may include:
a) missing instructions (that still compile)
b) misplaced instructions (wrong order)
c) unnecessary instructions that damage data

Note4: Memory leaks frequently do not cause immediate problems.
There is additional tool for Visual Studio line of compilers
implanted in the code to help you with detection of memory leaks

Note5: Some comments may try to trick you that an incorrect
instructions are in fact correct. It is the same way as if
they were written by an incompetent programmer who was adding
on to (i.e. "improving") an existing program and introduced
the errors. You were hired to clean the mess.

Note6: Use a HIGHLIGHTER to indicate your corrections
*/

#include <iostream>
using namespace std;

#ifdef unix
// on Linux size_t is not built-in type
#include <cstddef>
#endif

#ifdef _MSC_VER
// Microsoft compiler specific memory leak detection tool
#include <crtdbg.h>
#endif



class BadVector {
private:
    double *arr;
    size_t  siz;
    size_t  cap;
public:
    BadVector() : siz(0), cap(2) { arr = new double[cap]; }
    BadVector(const BadVector &copy);
    ~BadVector();
    void      operator=(const BadVector &copy);
    size_t    capacity() const { return(cap); }
    size_t    size() const { return(siz); }
    void      reserve(size_t newcap);
    void      resize(size_t newsiz);
    const double&   operator[](size_t ndx) const { return(arr[ndx]); }
    double&   operator[](size_t ndx) { return(arr[ndx]); }
    const double&   front() const { return(arr[0]); }
    double&   front() { return(arr[0]); }
    const double&   back() const { return(arr[siz - 1]); }
    double&   back() { return(arr[siz - 1]); }
    void      push_back(double x);
    void      pop_back() { if (siz>0) siz--; }
};

//* DO NOT MODIFY CODE ABOVE - IT IS CORRECT *





BadVector::BadVector(const BadVector &copy) : siz(copy.siz), cap(copy.siz) {
    arr = new double[cap];
    for (size_t i = 0; i<siz; i++) arr[i] = copy.arr[i];
}

BadVector::~BadVector() {
    delete[] arr;                      // garbage collection will deallocate the null pointer faster
}

void BadVector::operator=(const BadVector &copy) {  // void return is OK as long as we don't need to cascade assignments
    if (this != &copy) {
        if (cap<copy.siz) {
            delete[] arr;
            cap = copy.siz;
            arr = new double[cap];
        }

        siz = copy.siz;
        for (size_t i = 0; i<siz; i++) arr[i] = copy.arr[i];
    }
    // simplified: no return(*this) - void return is OK as long as no need for "a=b=c"
}

void BadVector::reserve(size_t newcap) {
    double *t;
    if (siz>newcap) siz = newcap; // truncate size if necessary
    t = new double[newcap];
    for (size_t i = 0; i<siz; i++) t[i] = arr[i];
    delete[] arr;
    cap = newcap;
    arr = t;
}

void BadVector::resize(size_t newsiz) {
    if (newsiz>cap) reserve(newsiz);
    siz = newsiz;
}

void BadVector::push_back(double x) {
    if (siz == cap) reserve(2 * cap);
    arr[siz] = x;
    siz++;
}



//* DO NOT MODIFY ANYTHING BELOW - IT IS CORRECT *


// It is done with some inefficiencies on purpose to horse testing of ceretain memory management operations

void FN(BadVector C) {
    // passing by value is used to test your copy constructor
    // in real life we would use passing by const reference
    cout << "C:";
    for (size_t i = 0; i<C.size(); i++) cout << " " << C[i];
    cout << endl;;
    C.reserve(C.capacity() * 5);
}


int main() {
    {
        size_t i;
        BadVector A, B;

        A.resize(3);
        for (i = 0; i<3; i++) A[i] = i;

        for (i = 3; i<10; i++) A.push_back(i);


        cout << "A:";
        for (i = 0; i<A.size(); i++) cout << " " << A[i];
        cout << endl;;

        B = A;

        while (A.size()>0) A.pop_back();

        for (i = 0; i<20; i++) A.push_back(i);

        cout << "A:";
        for (i = 0; i<A.size(); i++) cout << " " << A[i];
        cout << endl;;

        cout << "B:";
        for (i = 0; i<B.size(); i++) cout << " " << B[i];
        cout << endl;;

        B = B;

        cout << "B:";
        for (i = 0; i<B.size(); i++) cout << " " << B[i];
        cout << endl;;

        FN(B);

        cout << "B:";
        for (i = 0; i<B.size(); i++) cout << " " << B[i];
        cout << endl;;
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
