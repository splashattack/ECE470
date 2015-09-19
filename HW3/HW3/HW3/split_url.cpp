//* The test program for SplitURL function from Homework 2 - ECEx70 *


/**
    HW3
    file: split_url.cpp
    Author: Caleb Gill
*/
#include<iostream>
#include<string>
using namespace std;

void SplitURL(const string &url, string &type, string &host, string &page)
{
    // *** do not modify above (except for adding your homework header comment) ***
    unsigned int currentPos = 0;

    //TYPE
    if (url.find("://") != string::npos)
    {
        type = url.substr(0, url.find("://")); // extracts string containing type (http, etc.)
        currentPos = url.find("://") + 3; // update pos in url
    }
    else
    {
        type = "http"; // http by default
    }

    //HOST
    if (url.find("/", currentPos) != string::npos)
    {
        cout << "Found /" << endl;

        host = url.substr(currentPos, url.find("/",currentPos) - currentPos); // extracts all text until next "/" char to get host
        currentPos = url.find("/", currentPos); //update pos in string
    }
    else
    {
        host = url.substr(currentPos);
        currentPos = string::npos;
    }

    //PAGE
    if (currentPos != string::npos)
    {
        page = url.substr(currentPos);
    }
    else
    {
        page = "/";
    }
    // *** do not modify below ***
}

int main() {
    cout << "This is the test program for SplitURL function" << endl << endl;
    for (;;) {
        cout << "\nPlease enter the URL to split or q to quit" << endl;
        cout << "URL=";
        string U;
        cin >> U;
        if (U == "q") break;
        string T, H, P;
        SplitURL(U, T, H, P);
        cout << "TYPE: " << T << endl;
        cout << "HOST: " << H << endl;
        cout << "PAGE: " << P << endl;
    }
    cout << "Good bye!" << endl;
    return(0);
}