//* HW 6 - enhance the Count the frequency of occurrence program *


/*
* INSERT YOUR HW HEADER HERE
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

#ifdef unix
// on Linux size_t is not built-in type
#include <cstddef>
#endif

#ifdef _MSC_VER
// Microsoft compiler specific memory leak detection tool
#include <crtdbg.h>
#endif


class ItemCount {
private:
    string  name;
    size_t  cnt;
public:
    ItemCount() : name(""), cnt(0) {}
    ItemCount(const string &s) : name(s), cnt(0) {}
    ~ItemCount() {}

    void    print(ostream& out) const { out << setw(16) << name << setw(8) << cnt << endl; }
    void    OneMoreFound() { cnt++; }
    size_t  getCount() const { return(cnt); }
    int     hasSameName(const ItemCount& c) const { return(name == c.name); }
    int     hasSmallerCountThan(const ItemCount& c) const { return(cnt<c.cnt); }
};
//* DO NOT MODIFY FROM HERE UP EXCEPT THE CUSTOM HEADER *






//* TO DO: MAKE THE ARRAY-BASED DATA STRUCTURE EXPAND AS NECESSARY *




class Array_of_ItemCount {
private:
    size_t      siz;
    ItemCount   *arr;       // convert to pointer-based array
public:
    Array_of_ItemCount() : siz(0) {}
    Array_of_ItemCount(const Array_of_ItemCount &obj);
    const Array_of_ItemCount& operator=(const Array_of_ItemCount& other);
    ~Array_of_ItemCount();
    void    add(const string &name);
    void    sort();
    void    print(ostream &whereto) const;
    size_t  size() const { return(siz); }
};

Array_of_ItemCount::Array_of_ItemCount(const Array_of_ItemCount& obj) : siz(obj.siz)
{
    arr = new ItemCount[obj.siz];
    //*arr = *obj.arr;
    for (size_t i = 0; i < siz; i++)
    {
        arr[i] = obj.arr[i];
    }
}

Array_of_ItemCount::~Array_of_ItemCount()
{
    delete[] arr;
}

const Array_of_ItemCount& Array_of_ItemCount::operator=(const Array_of_ItemCount& other) {
    if (this != &other)
    {
        siz = other.siz;
        arr = new ItemCount[other.siz];
        for (size_t i = 0; i < other.siz; i++)
        {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

void Array_of_ItemCount::add(const string &name) {
    ItemCount current(name);
    for (size_t i = 0; i<siz; i++)
        if (arr[i].hasSameName(current)) {
            arr[i].OneMoreFound();
            return;
        }

    //allocate more space using temp
    ItemCount *temp = new ItemCount[siz + 1];
    for (size_t i = 0; i < siz; i++)
    {
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
    // append the new sequence at the end
    arr[siz] = current;
    arr[siz].OneMoreFound();
    siz++;
}

void Array_of_ItemCount::sort() {
    // sorting using insertion sort algorithm
    // this algorithm works best for partially sorted data
    // and will be discussed in the third portion of the course
    for (size_t i = 1; i<siz; i++) {
        ItemCount elem = arr[i];
        int j = static_cast<int>(i) - 1; // this must not be size_t as it may go down <0
        while (j >= 0 && arr[j].hasSmallerCountThan(elem)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = elem;
    }
}

void Array_of_ItemCount::print(ostream &whereto) const {
    for (size_t i = 0; i<siz; i++)
        arr[i].print(whereto);
}

//* DO NOT MODIFY FROM HERE DOWN *




void PRINT(Array_of_ItemCount P) {
    // note: P should be passed by const reference here
    //       it was passed by value only to test your work
    //       on Array_of_ItemCount class copy constructor
    cout << "           SSID    COUNT" << endl;
    P.print(cout);
}


int main() {
    {
        
        {
            Array_of_ItemCount A;
            Array_of_ItemCount B;
            string inName;
            cout << "Read data from: ";
            getline(cin, inName);
            ifstream inFile;
            inFile.open(inName.c_str());
            if (!inFile.is_open()) {
                cout << "ERROR: Cannot open " << inName << " file for reading." << endl;
                return(1);
            }

            size_t line = 0;
            for (;;) {
                string buffer;
                getline(inFile, buffer);
                if (inFile.fail()) break;

                line++;
                cout << line << " " << A.size() << "\r";

                if (buffer.empty() || buffer[0] == '#') continue;
                //!! why this line here?, why '#' and not "#"

                size_t p = buffer.find("(");
                if (p == string::npos) continue; // not found first (, proceed to the next line read
                size_t q = buffer.find(")", p);
                if (q == string::npos) continue; // not found first ) after first (, proceed to the next line read
                                                 //!! can you envision code without use of continue?

                A.add(buffer.substr(p + 2, q - p - 2));
            }
            inFile.clear();
            inFile.close();

            B = A; // let us keep the orginal data

            B.sort(); // and sort the copy
            PRINT(B);
        }
       
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
