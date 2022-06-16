/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA4
* Matrix.c
* Implementation file for Matrix ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Matrix.h"

// structs --------------------------------------------------------------------

// private EntryObj type
typedef struct EntryObj {
   int column;
   double value;
} EntryObj;

// private Entry type
typedef EntryObj* Entry;

// private MatrixObj type
typedef struct MatrixObj {
   int size;
   int NNZ;
   List* row;
} MatrixObj;



// newEntry() Used as a helper function
// Returns reference to new Entry object to insert in List ADT. 
Entry newEntry(int c, double v) {
   Entry E = malloc(sizeof(EntryObj));
   E->column = c;
   E->value = v;
   return(E);
}


// freeEntry() Used as a helper function
// Frees heap memory pointed to by *pE, sets *pE to NULL.
void freeEntry(Entry* pE){
   if(pE!=NULL && *pE!=NULL){
      free(*pE);
      *pE = NULL;
   }
}


// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
   Matrix M = malloc(sizeof(MatrixObj));
   M->size = n;
   M->NNZ = 0;
   M->row = malloc(sizeof(List) * (n+1));
   for(int i = 0;i < (n+1); i++) {
      M->row[i] = newList();
   }
   return(M); 
}


// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
   if(pM!=NULL && *pM!=NULL) {
      makeZero(*pM); 
      for(int i = 0; i < (size(*pM)+1); i++) { 
         freeList(&(*pM)->row[i]);   
         (*pM)->row[i] = NULL; 
      }
      free((*pM)->row);
   }
   free(*pM);
   *pM = NULL;
}


// Access functions

// size()
// Return the size of square Matrix M.
int size(Matrix M) {
   if(M == NULL) {
      printf("Matrix Error: calling size() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   return(M->size);
}


// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
   if(M == NULL) {
      printf("Matrix Error: calling NNZ() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   return(M->NNZ);
}


// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
   if(A == NULL||B == NULL) {
      printf("Matrix Error: calling equals() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   if(size(A) != size(B)) { // if sizes are not equal
      return(0);
   }
   for(int i = 1; i < (size(A)+1); i++) {
      List X = A->row[i];
      List Y = B->row[i];
      if(length(X) != length(Y)) {  // if the two rows are not the same length meaning different matrices
         return(0);
      }
      moveFront(X);
      moveFront(Y);
      while(index(X) >= 0) { 
         if(((Entry)get(X))->column != ((Entry)get(Y))->column) {  // if column is not the same (not equal)
            return(0);
         }
	 if(((Entry)get(X))->value != ((Entry)get(Y))->value) {  // if value is not the same (not equal)
            return(0);
         }
	 moveNext(X);
	 moveNext(Y);
      }
   }
   return(1);
}



// Manipulation procedures

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
   if(M == NULL) {
      printf("Matrix Error: calling makeZero() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   M->NNZ = 0;
   for(int i = 1; i < (size(M)+1); i++) {
      List L = M->row[i];
      moveFront(L);
      while(index(L) >= 0) {
         Entry R;
	 R = (Entry)get(L);
         freeEntry(&R);
	 moveNext(L);
      }
      clear(L);
   }
}



// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
   if(M == NULL) {
      printf("Matrix Error: calling changeEntry() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   if(i < 1 || i > size(M) || j < 1 || j >size(M)) {  // precond
      printf("Invalid row or column\n");
      exit(EXIT_FAILURE);
   }
   List L = M->row[i];
   if(x == 0) { //if it is 0 then delete the entry
      moveFront(L);
      while(index(L) >= 0 && ((Entry)get(L))->column < j) { // go through the list until column is greater or equal to j
         moveNext(L);
      }
      if(index(L) >= 0) {  //if at the end of list
         Entry E = get(L);  
         freeEntry(&E);
         delete(L);
         M->NNZ--;
      }
   }
   else {  // x is not 0
      if(length(L) == 0) {  // if list is empty
         append(L, newEntry(j,x));
         M->NNZ++;
      }
      else {  // if list has something
         moveFront(L);
         while(index(L) >= 0 && ((Entry)get(L))->column < j) {  // go through the list until column is greater or equal to j
	 moveNext(L);
      }
         if(index(L) == -1) {  // if list is empty
            append(L, newEntry(j,x));
            M->NNZ++;
         }
         else if(((Entry)get(L))->column == j) { // if column equals j
            ((Entry)get(L))->value = x;  // replace 
         }
         else {  // if j is before column
            insertBefore(L, newEntry(j,x));
            M->NNZ++;
         }
      }
   }
}



// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
   if(A == NULL) {
      printf("Matrix Error: calling copy() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   Matrix N = newMatrix(size(A));
   for(int i = 1; i < (size(A)+1); i++) {
      List LA = A->row[i];
      List LN = N->row[i];
      moveFront(LA);
      while(index(LA) >= 0) {
         Entry E = get(LA);
	 append(LN, newEntry(E->column, E->value));
	 moveNext(LA);
      }
   }
   N->NNZ = A->NNZ;
   return(N);
}


// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
   if(A == NULL) {
      printf("Matrix Error: calling transpose() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   Matrix T = newMatrix(size(A));
   for(int i = 1; i < (size(A)+1); i++) {
      List LA = A->row[i];
      moveFront(LA);
      while(index(LA) >= 0) {
         Entry E = get(LA); 
	 List LT = T->row[E->column];
         append(LT, newEntry(i, E->value));
         moveNext(LA);
      }
   }
   T->NNZ = A->NNZ;
   return(T);
}


// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
   if(A == NULL) {
      printf("Matrix Error: calling scalarMult() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   Matrix M = copy(A);
   if(x != 0) {  // if multiplier(x) is not 0
      for(int i = 1; i < (size(A) + 1); ++i) {
         List LM = M->row[i];
         moveFront(LM);
	 while(index(LM) >= 0) {
            ((Entry)get(LM))->value *= x;
	    moveNext(LM);
	 }
      }
   }
   else { // if multiplier is 0
      makeZero(M);
   }
   return(M);
}


// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
   if(A == NULL||B == NULL) {
      printf("Matrix Error: calling sum() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   if(size(A) != size(B)) {
      printf("Matrices are not equal sizes\n");
      exit(EXIT_FAILURE);
   }
   if(equals(A, B) == 1) {  // if they are the same it is the same as A+A or A times 2
      return(scalarMult(2, A));
   }
   Matrix S = newMatrix(size(A));
   for(int i = 1; i < (size(A) + 1); ++i) {
      List LA = A->row[i];
      List LB = B->row[i];
      List LS = S->row[i];
      moveFront(LA);
      moveFront(LB);
      while(index(LA)>= 0 && index(LB)>=0) { // go through both lists (if there are two lists)
         Entry EA = get(LA); 
         Entry EB = get(LB);
         if(EA->column < EB->column) {  // if two different columns
            append(LS, newEntry(EA->column, EA->value));
            S->NNZ++;
            moveNext(LA);
         }
	 else if(EB->column < EA->column) { // if two different columns
            append(LS, newEntry(EB->column, EB->value));
            S->NNZ++;
            moveNext(LB);
         }
         else {  // if the two columns are the same
            if((EA->value + EB->value) != 0) {  // if the values wont negate each other 
               append(LS, newEntry(EA->column, (EA->value + EB->value)));
	       S->NNZ++;
	    }
            moveNext(LA);
            moveNext(LB);
         }
      }
      while(index(LA) >= 0) {  // if there is only one list (A)
         Entry EA = get(LA);
         append(LS, newEntry(EA->column, EA->value));
         S->NNZ++;
         moveNext(LA);
      }
      while(index(LB) >= 0) { // if there is only one list (B)
         Entry EB = get(LB);
         append(LS, newEntry(EB->column, EB->value));
         S->NNZ++;
         moveNext(LB);
      }
   }
   return(S);
}


// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
   if(A == NULL||B == NULL) {
      printf("Matrix Error: calling diff() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   if(size(A) != size(B)) {
      printf("Matrices are not equal sizes\n");
      exit(EXIT_FAILURE);
   }
   Matrix D = newMatrix(size(A));
   if(equals(A, B) == 1) {  // if they are the same then they cancel out into an empty Matrix
      return(D);
   }
   for(int i = 1; i < (size(A) + 1); ++i) {
      List LA = A->row[i];
      List LB = B->row[i];
      List LD = D->row[i];
      moveFront(LA);
      moveFront(LB);
      while(index(LA)>=0 && index(LB)>=0) { // go through both lists (if there are two lists)
         Entry EA = get(LA); 
         Entry EB = get(LB); 
         if(EA->column < EB->column) {  // if two different columns
            append(LD, newEntry(EA->column, EA->value));
            D->NNZ++;
            moveNext(LA);
         }
         else if(EB->column < EA->column) { // if two different columns
            append(LD, newEntry(EB->column, (0-(EB->value))));
            D->NNZ++;
            moveNext(LB);
         }
         else {  // if the two columns are the same
            if((EA->value - EB->value) != 0) {  // if the values wont negate each other
               append(LD, newEntry(EA->column, (EA->value - EB->value)));
            }
            moveNext(LA);
            moveNext(LB);
         }
      }
      while(index(LA) >= 0) {  // if there is only one list(A)
         Entry EA = get(LA); 
         append(LD, newEntry(EA->column, EA->value));
         D->NNZ++;
         moveNext(LA);
      }
      while(index(LB) >= 0) { // if there is only one list(B)
         Entry EB = get(LB);
         append(LD, newEntry(EB->column, (0-(EB->value))));
         D->NNZ++;
         moveNext(LB);
      }
   }
   return(D);
}


// vectorDot() helper function for product()
// computes the vector dot product of two matrix rows represented by Lists P and Q
double vectorDot(List P, List Q) {
   double v = 0;
   moveFront(P);
   moveFront(Q);
      while(index(P)>=0 && index(Q)>=0) {
         Entry Ea = (Entry)get(P);
         Entry Eb = (Entry)get(Q);
         if(Ea->column < Eb->column) {  // if two different columns
            moveNext(P);
         }
         else if(Eb->column < Ea->column) { // if two different columns
            moveNext(Q);
         }
         else {  // if the columns are the same
            v+= Ea->value * Eb->value;
            moveNext(P);
            moveNext(Q);
         }
      }
   return(v);
}



// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
   if(A == NULL||B == NULL) {
      printf("Matrix Error: calling product() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   if(size(A) != size(B)) {
      printf("Matrices are not equal sizes\n");
      exit(EXIT_FAILURE);
   }
   B = transpose(B);
   Matrix M = newMatrix(A->size);
   for(int i=1; i<(M->size+1); i++) { // go through A
      List Lm = M->row[i];
      List La = A->row[i];
      if(length(La) != 0) {  //if A row is not empty 
         for(int j=1; j<(M->size+1); j++) { //go though transposed B
            List Lb = B->row[j];  
            double value = 0;
	    value = vectorDot(La, Lb);
            if(value != 0) {  // if the value is not 0 add it
               append(Lm, newEntry(j, value));
               M->NNZ++;
            }
         }
      }
   }
   freeMatrix(&B);
   return(M);
}


// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
   if(M==NULL) {
      printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }
   for(int i = 1; i<(size(M) + 1); i++) {
      if(length(M->row[i]) > 0) {
         fprintf(out, "%d:", i);
         List L = M->row[i];
         moveFront(L);
         while(index(L) >= 0) {  
            fprintf(out, " (%d, %0.1f)", ((Entry)get(L))->column, ((Entry)get(L))->value);
            moveNext(L);
         }
         fprintf(out, "\n");
      }
   }
}
