/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA4
* Sparse.c
* Main program for PA4 that does matrix operations
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Matrix.h"
#define MAX_LEN 300

int main(int argc, char* argv[]) {
   FILE* in; 
   FILE* out; 


   if(argc != 3) {
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }


   in = fopen(argv[1], "r");
   if(in==NULL) {
      printf("Unable to read from file %s\n", argv[1]);
      exit(EXIT_FAILURE);
   }


   out = fopen(argv[2], "w");
   if(out==NULL) {
      printf("Unable to write to file %s\n", argv[2]);
      exit(EXIT_FAILURE);
   }

   int n;
   int NNZA;
   int NNZB;


   fscanf(in, " %d", &n);
   fscanf(in, " %d", &NNZA);
   fscanf(in, " %d", &NNZB);

   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);

   int r;
   int c;
   double v;

   for(int i=0; i<NNZA; i++) {
      fscanf(in, " %d", &r);
      fscanf(in, " %d", &c);
      fscanf(in, " %lf", &v);
      changeEntry(A, r, c, v);
   }
   for(int i=0; i<NNZB; i++) {
      fscanf(in, " %d", &r);
      fscanf(in, " %d", &c);
      fscanf(in, " %lf", &v);
      changeEntry(B, r, c, v);
   }

   fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
   printMatrix(out, A);

   fprintf(out, "\nB has %d non-zero entries:\n", NNZ(B));
   printMatrix(out, B);


   fprintf(out, "\n(1.5)*A =\n");
   Matrix C = scalarMult(1.5, A);
   printMatrix(out, C);

   fprintf(out, "\nA+B =\n");
   Matrix D = sum(A, B);
   printMatrix(out, D);

   fprintf(out, "\nA+A =\n");
   Matrix E = sum(A, A);
   printMatrix(out, E);

   fprintf(out, "\nB-A =\n");
   Matrix F = diff(B, A);
   printMatrix(out, F);

   fprintf(out, "\nA-A =\n");
   Matrix G = diff(A, A);
   printMatrix(out, G);

   fprintf(out, "\nTranspose(A) =\n");
   Matrix H = transpose(A);
   printMatrix(out, H);

   fprintf(out, "\nA*B =\n");
   Matrix I = product(A, B);
   printMatrix(out, I);

   fprintf(out, "\nB*B =\n");
   Matrix J = product(B, B);
   printMatrix(out, J);
   fprintf(out, "\n");


   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);
   freeMatrix(&I);
   freeMatrix(&J);

   fclose(in);
   fclose(out);

   return(0);
}

