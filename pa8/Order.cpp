/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA8
* Order.cpp
* One of the two top-level clients for PA8 that
* takes two files, an input and output file.
* The program makes a Dictionary ADT from the
* input file and prints the alphabetical order 
* and pre-order tree walk to the output file
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

   int line_count;
   ifstream in;
   ofstream out;
   string line;

   // check command line for correct number of arguments
   if(argc != 3) {
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if(!in.is_open()) {
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if(!out.is_open()) {
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   // read each line of input file, then count and print tokens 
   line_count = 0;
   Dictionary D;
   while(getline(in, line)) {
      line_count++;
      D.setValue(line, line_count);
      line = "";
   }

   string val = D.to_string();
   string val1 = D.pre_string();
   out << val;

   out << val1;

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

