//Alphabetizer.h
//COMP 11 HW 4
//By Rebecca Redelmeier
//October 25, 2016
//Purpose: header file for Alphabetizer class. Reads in strings from file or
//         cin and couts them to user in forward or reversed order as 
//         requested.

#include "StringBST.h"
#include <fstream>

class Alphabetizer {
        public:
                Alphabetizer(); //default constructor
                ~Alphabetizer(); //default destructor
                void run(); //runs using cin strings
                void run(string, string); //runs using passed in file strings

        private:
                string sort_type;
                StringBST* stringTree;

                void error(string); //cerrs error message
                void copy_strings_from(istream&); //copies strings from file
                void print(string); //prints strings in specified order
};
