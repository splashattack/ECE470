///
///\file main.cpp
///\author Caleb Gill
///\brief ECE470, HW 4
///
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>

using namespace std;


struct file
{
    string name;
    ifstream instream;
    ofstream outstream;
    vector<double> legLength;
    vector<int> legCourse;
};

void parseFile(file &infile);
void parseLine(string currentLine, size_t currentLineNumber, vector<double> &legLength, vector<int> &legCourse);
void writeToOutput(file &outfile, string name);

double feetToMiles(double value) { return value / 5280; }


int main()
{
    file File;
    cout << "Please enter the name of the file you would like to parse." << endl;
    cin >> File.name;
    

    File.instream.open(File.name);
    parseFile(File);
    File.instream.close();
    writeToOutput(File, File.name.substr(0, File.name.find(".txt"))  + "_ouput.txt"); // remove .txt from file name and append _output.txt
}


void parseFile(file &infile)
{
	if (infile.instream.is_open())
	{
        size_t currentLineNumber = 0;
		while (!infile.instream.eof())
		{
            string currentLine;
			getline(infile.instream, currentLine);
            currentLineNumber++;
			parseLine(currentLine, currentLineNumber, infile.legLength, infile.legCourse);

		}
	}
	else
	{
		cerr << "Error: File could not be read because file is not open." << endl;
	}
}

void parseLine(string currentLine, size_t currentLineNumber, vector<double> &legLength, vector<int> &legCourse)
{
    if (regex_match(currentLine, regex("(^Trackpoint)(.*)"))) // Trackpoint at beginning of line	
    {
        if (regex_match(currentLine, regex("(.*)true$"))) // true at end of line
        {
            
            // Leg Length 
            double legLength_value = 0;
            string legLength_unit = "";
            if (currentLine.find(" f", currentLine.find(" f") + 1) != string::npos)
            {
                legLength_unit = "ft";
                size_t legLengthEndPos = currentLine.find(" f", currentLine.find(" f") + 1);
                size_t legLengthBeginPos = currentLine.rfind(" ", legLengthEndPos - 1);
                legLength_value = stod(currentLine.substr(legLengthBeginPos, legLengthEndPos - legLengthBeginPos));
            }
            else if (currentLine.find(" m", currentLine.find(" m") + 1) != string::npos)
            {
                legLength_unit = "mi";
                size_t legLengthEndPos = currentLine.find(" m");
                size_t legLengthBeginPos = currentLine.rfind(" ", legLengthEndPos - 1);
                legLength_value = stod(currentLine.substr(legLengthBeginPos, legLengthEndPos - legLengthBeginPos));
            }
            else
            {
                cerr << "Error ln " << currentLineNumber << ": Could not find leg length." << endl;
            }
            

            if (legLength_unit == "ft")
            {
                legLength_value = feetToMiles(legLength_value);
            }

            
            

            // Leg Course
            int legCourse_value = 0;
            if (currentLine.find("° ") != string::npos)
            {
                size_t legCourseEndPos = currentLine.find("° ");
                size_t legCourseStartPos = currentLine.rfind(" ", legCourseEndPos);
                legCourse_value = stoi(currentLine.substr(legCourseStartPos, legCourseEndPos - legCourseStartPos));
            }
            else
            {
                cerr << "Error ln " << currentLineNumber << ": Could not find Leg Course." << endl;
            }


            if (legLength_value != 0)
            {
                legLength.push_back(legLength_value);
                legCourse.push_back(legCourse_value);
            }

            
        }
        else
        {
            cerr << "Error ln " << currentLineNumber << ": Could not parse line." << endl;
        }
    }
}


void writeToOutput(file &outfile, string name)
{
    
    outfile.outstream.open(name);
    outfile.outstream << name << endl << endl
                      << "Leg Length, Leg Course" << endl;

    outfile.legCourse.push_back(0); // append 0 at end of file to avoid indexing error.

    double legLength_sum = 0;
    for (size_t iter = 0; iter < outfile.legCourse.size() - 1; iter++)
    {
        legLength_sum += outfile.legLength[iter];

        if (outfile.legCourse[iter + 1] != outfile.legCourse[iter])
        {
            
            if (legLength_sum > outfile.legLength[iter])
            {
                // Now that the course has changed, we can output the previously added values
                outfile.outstream << legLength_sum << setprecision(4) << setw(8) << outfile.legCourse[iter] << setw(8) << endl;
            }
            else
            {
                outfile.outstream << outfile.legLength[iter] << setprecision(4) << setw(8) << outfile.legCourse[iter] << setw(8) << endl;
            }
            legLength_sum = 0;
        }
    }
    outfile.outstream.close();
}