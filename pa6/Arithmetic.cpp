/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA6
* Arithmetic.cpp
* Main program for PA6
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

   ifstream in;
   ofstream out;
   

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}
