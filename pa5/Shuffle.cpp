/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA5
* Shuffle.cpp
* Main program for PA5 that does perfect shuffles on a "deck" of cards 
* until it is in its original order.
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

#define MAX_LEN 300

// alter its List& (List reference) argument D by performing one shuffle operation
void shuffle(List& D) {
   List F;
   List G;
   int l = D.length();
   int f = l/2;

   F.moveFront();
   D.moveFront();  
   G.moveFront();
   for(int i = 0; i<(f); i++) {
      F.insertAfter(D.peekNext());
      F.moveNext();
      D.moveNext();
   }
   for(int i = 0; i<(l-f); i++) {
      G.insertAfter(D.peekNext());
      G.moveNext();
      D.moveNext();
   }
   D.clear();
   D.moveFront();
   F.moveFront();
   G.moveFront();
   for(int i = 0; i<G.length(); i++) {
      D.insertAfter(G.peekNext());
      D.moveNext();
      G.moveNext();
      if(F.position() < F.length()) {
         D.insertAfter(F.peekNext());
         D.moveNext();
	 F.moveNext();
      }
   }
}   


int main(int argc, char * argv[]){
   if( argc != 2 ){
      cerr << "Usage: " << argv[0] << " number " << endl;
      return(EXIT_FAILURE);
   }
   int n = atoi(argv[1]);
   int s;
   List A;
   cout << "deck size       shuffle count " << endl;
   cout << "------------------------------" << endl;
   for(int i = 1; i <= n; i++) {
      cout << " " << i << "\t\t";
      for(int x = 0; x<i; x++) {
         A.insertBefore(x);
      }
      List B = A;
      shuffle(A);
      s = 1;
      while(true) {
         if(B == A) {
            break;
	 }
         shuffle(A);
	 s++;
      }
      cout << s << endl;
      A.clear();
      B.clear();

   }

   return(EXIT_SUCCESS);
}
