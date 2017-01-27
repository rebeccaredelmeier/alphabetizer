//Alphabetizer.cpp
//COMP 11 HW 4
//By Rebecca Redelmeier
//October 25, 2016
//Purpose: implimentation of Alphabetizer class. Reads in strings from file or
//         cin and couts them to user in forward or reversed order as requested
//

#include<fstream>
#include "Alphabetizer.h"
#include<iostream>

using namespace std;

/////////////////////////////////////
////////////PUBLIC FUNCTIONS/////////
/////////////////////////////////////

//Purpose: default constructor
//Arguments: none
//Returns: none
Alphabetizer::Alphabetizer()
{
        stringTree = new StringBST;
}

//Purpose: default destructor, deletes/recycles all allocated memory
//Arguments: none
//Returns: none
Alphabetizer::~Alphabetizer()
{
        while (!stringTree->isEmpty())
                delete stringTree;
}

//Purpose: runs alphabetizing function using cin
//Arguments: none
//Returns: none
void Alphabetizer::run()
{
        cin >> sort_type;
        if (sort_type != "f" and sort_type != "r") {
                error("Command Line: invalid sort type");
        }
        copy_strings_from(cin);       
        
        print("cin");
}

//Purpose: runs alphabetizing function using passed in file
//Arguments: string, string
//Returns: none
void Alphabetizer::run(string file_name, string sort)
{
        ifstream input;
        sort_type = sort;

        input.open(file_name);
        if (not input.is_open())
                error ("Usage: alphabetizer " + file_name);

        copy_strings_from(input);
        input.close();
        print(file_name);
}

/////////////////////////////////////
//////////PRIVATE FUNCTIONS//////////
/////////////////////////////////////

//Purpose: reads strings from passed in file
//Arguments: istream address
//Returns: none
void Alphabetizer::copy_strings_from(istream &infile)
{
        string s;

        for (infile >> s; not infile.eof(); infile >> s)
                stringTree->add(s);
}

//Purpose: cerr's error message
//Arguments: string
//Returns: none
void Alphabetizer::error(string message)
{
        cerr << message << endl;
        exit(1);
}

//Purpose: prints out stringTree alphabetically forwards or back
//Arguments: string
//Returns: none
void Alphabetizer::print(string file_type)
{
        cout << "[ " << file_type << ", " << sort_type << " : ";

        string to_print = "";

        //prints first word without a comma preceding it
        if (sort_type == "f") {
                to_print = stringTree->getMin();
                stringTree->removeMin();
        } else {
                to_print = stringTree->getMax();
                stringTree->removeMax();
        }
        cout << to_print;

        //goes through all other nodes and gets, removes, prints max or min
        //as indicated till all nodes have been printed and therefore removed.
        //Included proper formatting.
        while (!stringTree->isEmpty()) {
                if (sort_type == "f") { //print in order
                        to_print = stringTree->getMin();
                        stringTree->removeMin();
                } else { //print reversed order
                        to_print = stringTree->getMax();
                        stringTree->removeMax();
                }
                cout << ", " << to_print;
        }
        cout << " ]";
}
