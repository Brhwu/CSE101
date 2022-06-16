/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA6
* BigInteger.cpp
* Implementation file for BigInteger ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdlib.h> //added
#include"List.h"
#include"BigInteger.h"
#define POWER 9
#define BASE 1000000000


// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
   signum = 0;
   digits.clear(); //?
}
 

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
   if(s == "") {
      throw std::invalid_argument("BigInteger: Constructor: empty string");
   }
   signum = 0;
   digits.clear();
   int l = 0;
   //int p = 0;

   
   std::string temp = "";
   std::string c = ""; 
   c = s.at(0);
   if(c == "+") {
      signum = 1;
      //std::cout<< "plus" << std::endl;
      l++;
   }
   else if(c == "-") {
      signum = -1;
      //std::cout<< "minus" << std::endl;
      l++;
   }
   else {
      signum = 1;
      //std::cout<< "neutral" << std::endl;
   }
   temp = "";
   c.clear();
    
   int a = s.length();
   //std::cout<< "a= " << a << std::endl;

   digits.moveFront();
   int o = ((a) % POWER); //odd ones out
   int m = 0;  
   if(o != 0) {
      //std::cout<< "odd" << std::endl;
      temp = s.substr(l, o);
      digits.insertAfter(stol(temp));
      digits.moveNext();
      temp = "";
      l = o;   //+1 breaks it
      m = l + POWER;

      int z = s.length();
      while(m <= z) {
         temp = s.substr(l, m);
	 digits.insertAfter(stol(temp));
         digits.moveNext();
         temp = "";
         l = l + POWER;
         m = m + POWER;
      }
   } 
   else {
      //std::cout<< "start" << std::endl;
      m = ((l + POWER)-1);
      //std::cout<< "l1= " << l << std::endl;
      //std::cout<< "m1= " << m << std::endl;
      temp = s.substr(l, m);
      digits.insertAfter(stol(temp));
      digits.moveNext();
      temp = "";
      l = m;
      m = l + POWER-1;
      int z = s.length();
      while(m <= z) {
	 //std::cout<< "1l= " << l << std::endl;
         //std::cout<< "1m= " << m << std::endl;
	 //temp = "";
         temp = s.substr(l, m);
         digits.insertAfter(stol(temp));
         digits.moveNext();
         temp = "";
         l = l + POWER;
         m = m + POWER;
      }
   }

}


// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
   signum = N.signum;
   digits.clear();
   digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
   return(signum);
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {   //need to check proper code
   if(this->signum == N.signum && this->digits == N.digits) { // this == N?
      return 0;
   }
   if(this->signum < N.signum) {  
      return -1;
   }
   if(this->signum > N.signum) {
      return 1;
   }
   if(this->digits.length() < N.digits.length()) {
      return (this->signum * -1);
   }
   if(this->digits.length() > N.digits.length()) {
      return (this->signum);
   }
   List T, X;
   T = this->digits;
   X = N.digits;
   T.moveFront();
   X.moveFront();  
   while(T.position() != ((T.length())-1)) {
      if(T.peekNext() < X.peekNext()) {
         return(-1 * this->signum);
      }
      if(T.peekNext() > X.peekNext()) {
         return(this->signum);
      }
      T.moveNext();
      X.moveNext();
   }
   return(0);
}





  
// Helper functions --------------------------------------------------------
// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L) {
   L.moveFront();
   while(L.position() == (L.length()-1)) {
      L.setAfter(L.peekNext() * -1);
      L.moveNext();
   }
}


// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn) {
   S.clear();
   S.moveBack();
   A.moveBack();  //back ones to tens
   B.moveBack();
   while(A.position() != 0 && B.position() != 0) {  //which ever condition triggers is the shorter one
      S.insertAfter(A.peekPrev() + (B.peekPrev() * sgn));
      //S.movePrev();
      A.movePrev();
      B.movePrev();
   }
   while(A.position() != 0) {  // continue the list
      S.insertAfter(A.peekPrev());
      //S.movePrev();
      A.movePrev();
   }
   while(B.position() != 0) {
      S.insertAfter(B.peekPrev() * sgn);
      //S.movePrev();
      B.movePrev();
   }
   //std::cout << "S = " << S << std::endl;
   
}



// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
void normalizeList(List& L) {  //altered from the original
   L.moveBack();
   //std::cout << "Ln = " << L << std::endl;
   int carryover = 0;
   //int r = 0;
   while(L.position() != 0) {
      if(carryover != 0) {
	 L.setBefore(L.peekPrev() + carryover);
	 carryover = 0;
      }
      if(L.peekPrev() > BASE) {  // positive
	 carryover = 0;
         carryover = L.peekPrev() / BASE;
	 L.setBefore(L.peekPrev() % BASE);
      }
      if(L.peekPrev() < 0) {
	 carryover = 0;
	 //if(L.position() == 1) {  // if the highest number is carried over that means negative
	 //   r = -1;
	 //}
	 while(L.peekPrev() < 0) {
            L.setBefore(L.peekPrev() + BASE);  //not sure if used for mult
	    carryover--;
	 }
      }
      L.movePrev();
   }
   if(carryover != 0) {
      //L.setAfter(BASE + carryover);
      //carryover = 0;
      if(L.peekNext() < 0) {
	 L.moveBack();
         while(L.position() != 0) {
	    L.setBefore((L.peekPrev()-BASE) * -1);
	    L.movePrev();
	 }	    
      }
   }
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p) {
   L.moveBack();
   for(int i = 0; i < p; i++) {
      L.insertBefore(0);
   }
}


// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m) {
   L.moveFront();
   while(L.position() != (L.length()-1)) {
      L.setAfter(L.peekNext() * m);
      L.moveNext();
   }

}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
   this->digits.clear();
   signum=0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
   if(this->signum == 0) {
   }
   else {
      signum = signum * -1;
   }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
   BigInteger R;
   BigInteger M = N;
   //BigInteger A = this;
   //List A = this->digits;
   //List B = N.digits,
   if(this->signum == 0) {  // 0+N  0+B
      R.digits = N.digits;
      R.signum = N.signum;
   }
   if(N.signum == 0) {  // this+0  A+0
      R.digits = this->digits;
      R.signum = this->signum;
   }
   if(this->signum == -1 && N.signum == 1) { // -this+N or N+-this  A+-B A-B  
      sumList(R.digits, N.digits, this->digits, -1);
      normalizeList(R.digits);
      M.signum = -1;
      R.signum = ((this->BigInteger::compare(M)) * -1);    // if this is greater than N then negative
   }
   if(this->signum == 1 && N.signum == -1) { // this + -N   A + -B 
      sumList(R.digits, this->digits, N.digits, -1);
      //std::cout << "R = " << R << std::endl;
      //std::cout << "R = " << R.sign() << std::endl;
      normalizeList(R.digits);
      //std::cout << "R = " << R << std::endl;
      //std::cout << "R = " << R.sign() << std::endl;
      //R.signum = ((N.BigInteger::compare(this)) * -1);    // if N is greater than this then negative
      M.signum = 1;
      R.signum = ((this->BigInteger::compare(M)) * 1);    // if this is greater than N then positive
      //std::cout << "R = " << R.sign() << std::endl;
   }
   else { List T, X;  // A+B
   T = this->digits;
   X = N.digits;
   sumList(R.digits, T, X, 1);
   //std::cout<< "add";
   //std::cout<< "R= "<< R.digits;
   normalizeList(R.digits);
   R.signum = 1;
   }
   return R;
}
 


   

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
   BigInteger R;
   BigInteger M = N;
   if(this->signum == 0) {  // 0 - N
      R.digits = N.digits;
      //negateList(R.digits);
      R.signum = (-1 * N.signum);
   }
   if(N.signum == 0) {  // this - 0
      R.digits = this->digits;
      R.signum = this->signum;
   }
   if(this->signum == -1 && N.signum == 1) { // -this - N or -this + -N
      sumList(R.digits, N.digits, this->digits, 1);
      normalizeList(R.digits);
      R.signum = -1;
   }
   if(this->signum == 1 && N.signum == -1) { // this - - N or this + N
      sumList(R.digits, this->digits, N.digits, 1);
      normalizeList(R.digits);
      R.signum = 1;
   }
   if(this->signum == -1 && N.signum == -1) { // -this - - N or -this + N
      sumList(R.digits, N.digits, this->digits, -1);
      normalizeList(R.digits);
      //M.signum = 1;
      R.signum = ((this->BigInteger::compare(M)) * -1);
      //R.signum = 1;
   }
   if(this->signum == 1 && N.signum == 1) { // this - N or this - N
      sumList(R.digits, this->digits, N.digits, -1);
      normalizeList(R.digits);
      //M.signum = 1;
      R.signum = ((this->BigInteger::compare(M)));
      //R.signum = 1;
   }

   //sumList(R.digits, this->digits, N.digits, 1);
   //normalizeList(R.digits);
 
   return R;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
   BigInteger R;
   return R;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
   std::string s = "";
   if(this->signum == 0) {
      s += "0";
      return s;
   }
   if(this->signum == -1) {
      s += "-";
   }
   s += this->digits.to_string();
   return s;
}


// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<(std::ostream& stream, BigInteger N) {
   return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==(const BigInteger& A, const BigInteger& B) {
   bool eq = false;
   int c = 0;
   int ch = A.BigInteger::compare(B);
   eq = (c == ch);
   return(eq);
}


// operator<()
// Returns true if and only if A is less than B. 
bool operator<(const BigInteger& A, const BigInteger& B) {
   bool eq = false;
   int c = -1;
   int ch = A.BigInteger::compare(B);
   eq = (c == ch);
   return(eq);
}


// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=(const BigInteger& A, const BigInteger& B) {
   bool eq = false;
   int c = 0;
   int cc = -1;
   int ch = A.BigInteger::compare(B);
   eq = (c == ch || cc == ch);  
   return(eq);
}


// operator>()
// Returns true if and only if A is greater than B. 
bool operator>(const BigInteger& A, const BigInteger& B) {
   bool eq = false;
   int c = 1;
   int ch = A.BigInteger::compare(B);
   eq = (c == ch);
   return(eq);
}


// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=(const BigInteger& A, const BigInteger& B) {
   bool eq = false;
   int c = 0;
   int cc = 1;
   int ch = A.BigInteger::compare(B);
   eq = (c == ch || cc == ch);
   return(eq);
}




// operator+()
// Returns the sum A+B. 
BigInteger operator+(const BigInteger& A, const BigInteger& B) {
   //BigInteger X = A;
   //BigInteger Y = B;
   BigInteger R = A.add(B);
   return(R);
}


// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=(BigInteger& A, const BigInteger& B) {
   A = A.add(B);
   return(A); 
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-(const BigInteger& A, const BigInteger& B) {
   BigInteger R = A.sub(B);
   return(R);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=(BigInteger& A, const BigInteger& B) {
   A = A.sub(B);
   return(A);
}


// operator*()
// Returns the product A*B. 
BigInteger operator*(const BigInteger& A, const BigInteger& B) {
   BigInteger R = A.mult(B);
   return(R);
}


// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=(BigInteger& A, const BigInteger& B) {
   A = A.mult(B);
   return(A);
}
