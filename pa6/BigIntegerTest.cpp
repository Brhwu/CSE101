/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA6
* BigIntegerTest.cpp
* Test file for BigInteger ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

    BigInteger A = BigInteger("+111122223333");
    BigInteger B = BigInteger("+222211110000");


    cout << "A = " << A << endl;
    cout << "A = " << A.sign() << endl;
    cout << "B = " << B << endl;
    cout << "B = " << B.sign() << endl;

    // pos + pos = pos
    BigInteger D = BigInteger("-333333333333");
    BigInteger C = A + B;

    //-> pos + neg > 0
    B = BigInteger("-110122223333");
    cout << "D " << endl;
    D = BigInteger("1000000000");
    cout << "D1 " << endl;
    C = A + B;
    cout << "A = " << A << endl;
    cout << "A = " << A.sign() << endl;
    cout << "B = " << B << endl;
    cout << "B = " << B.sign() << endl;
    cout << "C = " << C << endl;
    cout << "C = " << C.sign() << endl;
    cout << "D = " << D << endl;
    cout << "D = " << D.sign() << endl;

    cout << "C = " << C << endl;
    cout << "C = " << C.sign() << endl;
    cout << "D = " << D << endl;
    cout << "D = " << D.sign() << endl;
    BigInteger E = C + D;
    cout << "E = " << E << endl;
    cout << "E = " << E.sign() << endl;

    // add a positive and a negative integer
    //-> pos + neg = 0
    B = BigInteger("-111122223333");
    C = A + B;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl; 
 


}    
