//main.cpp
//COMP 11 HW 4
//By: Rebecca Redelmeier
//Date: October 27, 2016
//Purpose: main() for constructing the Alphabetizer class. Can receive
//         command line arguments indicating a file to read in and
//         sort type. Calls appropriate Alphabetizer run() function based
//         on command line arguments.

#include"Alphabetizer.h"
#include<iostream>
#include<string>

using namespace std;

int main(int argc, char* argv[]) 
{
        Alphabetizer alpha;
        
        //no command line arguments, call run function without
        //parameters        
        if (argc == 1)
               alpha.run();

        //correct amount of command line arguments for reading
        //from file. call run function with parameters
        else if (argc == 3) {
               string order = argv[1];
               string file_name = argv[2];
               alpha.run(file_name, order);

        //incorrect amount of command line arguments. tell user.
        } else {
               cerr << "Usage: alphabetizer ";
               if (argc == 2)
                        cerr << argv[2];
               else
                        cerr << "unknown";
               cerr << endl;
               return 1;
        } 
        return 0;
}
