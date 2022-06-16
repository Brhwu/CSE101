/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA7
* DictionaryTest.cpp
* Test file for Dictionary ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

   string s;
   int x;
   string S[] = {"one", "two", "foo", "bar", "happy", "is", "three", "par"};

   Dictionary A;
   Dictionary B;
   Dictionary Z;

   cout << endl;

   // insert some pairs into A
   for(int i=0; i<8; i++){
      A.setValue(S[i], i+1);
   }
   //cout << "Done" << endl;
   // call operator=()
   B = A;
   Z = A;
   
   cout << "A.size() = " << A.size() << endl  << A << endl;

   cout << "A.contains(one) = " << A.contains("one") << endl;
   cout << "A.getValue(one) = " << A.getValue("one") << endl;
   cout << "A.hasCurrent() = " << A.hasCurrent() << endl;
   A.begin();
   cout << "A.Begin A.hasCurrent() = " << A.hasCurrent() << endl;
   cout << "A.currentKey() = " << A.currentKey() << endl;
   cout << "A.currentVal() = " << A.currentVal() << endl;
   A.next();
   cout << "A.next()" << endl;
   cout << "A.currentKey() = " << A.currentKey() << endl;
   cout << "A.currentVal() = " << A.currentVal() << endl;
   //cout << "A.hasCurrent() = " << A.hasCurrent() << endl;
   A.end();
   cout << "A.End A.hasCurrent() = " << A.hasCurrent() << endl;
   cout << "A.currentKey() = " << A.currentKey() << endl;
   cout << "A.currentVal() = " << A.currentVal() << endl;
   A.prev();
   cout << "A.prev()" << endl;
   cout << "A.currentKey() = " << A.currentKey() << endl;
   cout << "A.currentVal() = " << A.currentVal() << endl;

   A.clear();
   cout << "A.clear()" << endl;
   cout << "A.size() = " << A.size() << endl  << A << endl;

   //cout << "A.getValue(one) = " << A.getValue("one") << endl;
   A = Z;
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "B.contains(is) = " << B.contains("is") << endl;
   cout << "B.getValue(foo) = " << B.getValue("foo") << endl;

   B.setValue("bar", 9);
   
   // call copy constructor
   Dictionary C = B;
   
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;
   
   // check operator==()
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==A is " << (C==A?"true":"false") << endl << endl;

   // perform alterations on A
   cout << A.getValue("happy") << endl;
   A.getValue("happy") *= 10; // change the value associated with "happy"
   cout << A.getValue("happy") << endl << endl;
   A.remove("one");
   A.remove("two");

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << A.pre_string() << endl;

   // do forward iteration on B
   for(B.begin(); B.hasCurrent(); B.next()){
      s = B.currentKey();
      x = B.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;

   // do reverse iteration on C
   for(C.end(); C.hasCurrent(); C.prev()){
      s = C.currentKey();
      x = C.currentVal();
      cout << "("+s+", " << x << ") ";
   }
   cout << endl << endl;
   
   // check exceptions
   try{
      A.getValue("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.remove("blah");
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentKey();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.currentVal();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }  
   try{
      A.next();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.prev();
   }catch(logic_error& e){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   } 

   cout << endl;  

   return( EXIT_SUCCESS );
}
