/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA3
* FindComponents.c
* Main program for PA3 to find the all strongly connected components
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]) {
   FILE *in, *out;

   // check command line for correct number of arguments
   if(argc != 3) {
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open input file for reading and writing
   in = fopen(argv[1], "r");
   if(in==NULL) {
      printf("Unable to read from file %s\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if(out==NULL) {
      printf("Unable to write to file %s\n", argv[2]);
      exit(1);
   }

   // read input file
   // get first line (num of vertices)
   int num;
   fscanf(in, "%d", &num);

   Graph G = newGraph(num);

   int start, finish;

   // get first and second numbers on line
   // add directed edges(assemble graph)
   fscanf(in, "%d", &start);
   fscanf(in, "%d", &finish);
   while(start != 0 && finish != 0) {
      addArc(G, start, finish);
      fscanf(in, "%d", &start);
      fscanf(in, "%d", &finish);
   }

   // print adjacency list rep(first part of output)
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);

   // initalize List for DFS (goes from 1-n)
   List L = newList();
   for(int i = 1; i < num+1; ++i) {
      append(L, i);
   }

   DFS(G, L);  // run DFS on G

   Graph T = transpose(G);  // compute the transpose of G
   DFS(T, L); // run DFS on G transpose

   // get total number of strong connected components
   int c = 0;
   moveFront(L);
   while(index(L) != -1) {
      if(getParent(T, get(L)) == NIL) { 
         ++c;
      }
   moveNext(L);
   }

   // start second part of output
   fprintf(out, "\n");
   fprintf(out, "G contains %d strongly connected components:", c);

   // get strongly connect components
   int x = 0;  // used to list components (1, 2, ect)
   moveBack(L); // pop off stack
   while(index(L) != -1) {
      ++x;
      fprintf(out, "\n");
      fprintf(out, "Component %d:", x);
      int y = 0;
      while(y != -1) {  // count how far cursor goes back
         ++y;
         if(getParent(T, get(L)) == NIL) { // if there is a strong connected component (NIL)
            break;
         }
         movePrev(L);
         if(index(L) == -1) {  // if at end of List
            moveFront(L);
            break;
         }
      }
      
      fprintf(out, "%d ", get(L));  // prints first SCC
      for(int k = 0; k < y - 1; ++k) {  // go forward (minus 1 since first is printed)
         moveNext(L);
         fprintf(out, "%d ", get(L));  
      }

      for(int k = 0; k < y; ++k) {  // go back to original position in List
         movePrev(L);
      }
   }
   
   fprintf(out, "\n");

   freeGraph(&G);
   freeGraph(&T);
   freeList(&L);

   fclose(in);
   fclose(out);

   return(0);
}

