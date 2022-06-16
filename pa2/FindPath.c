/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA2
* FindPath.c
* Main program for PA2 to find the shortest path of a graph using BFS
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

   int num;

   // get first line (num of vertices)
   fscanf(in, "%d", &num);

   Graph G = newGraph(num);

   int start, finish;

   // get first and second numbers on line first part
   fscanf(in, "%d", &start);
   fscanf(in, "%d", &finish);
   while(start != 0 && finish != 0) {
      addEdge(G, start, finish);
      fscanf(in, " %d", &start);
      fscanf(in, " %d", &finish);
   }

   List source = newList();
   List dest = newList();
   List path = newList();
   fscanf(in, "%d", &start);
   fscanf(in, "%d", &finish);

   // second part queues paths
   while(start != 0 && finish != 0) {
      append(source, start);
      append(dest, finish);
      fscanf(in, "%d", &start);
      fscanf(in, "%d", &finish);
   }


   // first part of output
   printGraph(out, G);
	
   // second part 
   while(length(source) != 0) {
      fprintf(out, "\n");
      // get path
      start = front(source);
      deleteFront(source);
      finish = front(dest);
      deleteFront(dest);
      BFS(G, start);
      clear(path);
      getPath(path, G, finish);
      if(front(path) == NIL) { //if there is no path
         fprintf(out, "The distance from %d to %d is infinity\n", start, finish);
         fprintf(out, "No %d-%d path exists\n", start, finish);
      }
      else {  //there is a path
         fprintf(out, "The distance from %d to %d is %d\n", start, finish, getDist(G, finish));
         fprintf(out, "A shortest %d-%d path is: ", start, finish);
         printList(out, path);
         fprintf(out, "\n");
      }
   }

   freeGraph(&G);
   freeList(&source);
   freeList(&dest);
   freeList(&path);

   fclose(in);
   fclose(out);

   return(0);
}


