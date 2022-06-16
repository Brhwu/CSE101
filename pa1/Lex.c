/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA1
* Lex.c
* Main program for PA1 to sort text files in lexicographic order
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#define MAX_LEN 300

int main(int argc, char * argv[]) {
   int line_count;
   char temp[MAX_LEN];
   FILE *in, *out; 
   List tempList = newList();

   // check command line for correct number of arguments (from FileIO.c)
   if(argc != 3) {
      fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open input file for reading (from FileIO.c)
   in = fopen(argv[1], "r");
   if(in==NULL) {
      fprintf(stderr, "Unable to read from file %s\n", argv[1]);
      exit(1);
   }

   // open output file for writing (from FileIO.c)
   out = fopen(argv[2], "w");
   if( out==NULL ) {
      fprintf(stderr, "Unable to write to file %s\n", argv[2]);
      exit(1);
   }

   // sets lines to #of lines in FILE in (from FileIO.c)
   line_count = 0;
   while( fgets(temp, MAX_LEN, in) != NULL) {
      line_count++;
   }

   fclose(in);

   char** strArr = (char **)malloc(line_count * sizeof(char*));
   for(int i = 0; i < line_count; i++) {
      strArr[i] = (char *)malloc(MAX_LEN * sizeof(char));
   }

   in = fopen(argv[1], "r");
   line_count = 0;
   while(fgets(temp, MAX_LEN, in) != NULL) {
      strcpy(strArr[line_count], temp);
      line_count++;
   }

   for (int i = 0; i < line_count; i++) {
      moveBack(tempList);
      while(index(tempList) > -1 && strcmp(strArr[i], strArr[get(tempList)]) < 0) { 
         movePrev(tempList);
      }
      if(index(tempList) > -1) {
         insertAfter(tempList, i);
      }
      else {
         prepend(tempList, i);
      }
   }

   moveFront(tempList);
   while(index(tempList) > -1) {
      fprintf(out, "%s", strArr[get(tempList)]);
      moveNext(tempList);
   }

   for(int i = 0; i < line_count; i++) {
      free(strArr[i]);
   }
   free(strArr);

   freeList(&tempList);
   tempList = NULL;

   fclose(in);
   fclose(out);

   return(0);
}
