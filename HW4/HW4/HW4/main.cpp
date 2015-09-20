///
///\file main.cpp
///\author Caleb Gill
///\brief This is a brief discription
///
#include <iostream>
#include <fstream>
#include <string>

using namespace std;



void parseLine(ifstream &infile, string &foo, string &bar);


int main()
{

}




void parseFile(ifstream &infile)
{
	if (infile.is_open() && )
	{
		string currentLine;
		
		while (!infile.eof)
		{
			getline(infile, currentLine);
			parseLine(currentLine);
		}
	}
	else
	{
		cerr << "Error: Line could not be read because file is not open." << endl;
	}
}

void parseLine(string &currentLine)
{
	if (currentLine.find("Trackpoint") == 0 &&					// Trackpoint at beginning of line
		currentLine.find("true") == (currentLine.length() - 4))	// true at end of line
	{

	}

}

void writeToOutput(ofstream &outfile, string foo, string bar)
{

}