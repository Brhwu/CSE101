/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA8
* WordFrequency.cpp
* One of the two top-level clients for PA8 that 
* takes two files, an input and output file.
* The program makes a Dictionary ADT from the
* input file with the words on the file being the key and 
* the frequency of the word in the file being the value and will
* print the alphabetical order of the Dictionary ADT in the output file
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string token;
   //string delim = " "; 
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

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
   Dictionary D;
   // read each line of input file, then count and print tokens 
   while(getline(in, line))  {
      len = line.length();
      // get first token
      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);

      while(token!="") {  // we have a token
         // update token buffer
	 
         for(size_t i = 0; i < token.length(); i++) {
            token[i] = tolower(token[i]);
  	 }
         if(D.contains(token) == true) {
            D.setValue(token, (D.getValue(token)+1));
         }
         else {
            D.setValue(token, 1);
         }

         // get next token
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
      }
   }
   string val = D.to_string();

   out << val;


   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}
