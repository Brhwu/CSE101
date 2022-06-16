/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA1
* ListTest.c
* File to test List.c Functions
*********************************************************************************/

#include<stdio.h>  
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"


int main(int argc, char* argv[]) { //took the tests from TestClient.c and added a few more tests.
   
   List A = newList();
   List B = newList();
   List C = NULL;
   int i;

   for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i);
   }

   for(i=1; i<=20; i++){
      deleteBack(A);
      deleteFront(B);
      if(i == 5) {
	      printList(stdout, A);
	      printf("\n");
	      printList(stdout, B);
	      printf("\n");
      }
      if(i == 15) {
              printList(stdout, A);
	      printf("\n");
              printList(stdout, B);
	      printf("\n");
      }
   }
   printList(stdout, A);
   //printf("hi");
   printList(stdout, B);


   for(i=4; i<=25; i++){
      append(A,i);
      prepend(B,i);
   }



   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");

   C = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");


   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, -1);            // at index 6
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, -2);
   for(i=0; i<5; i++) movePrev(A); // at index 10
   delete(A);
   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);

   return(0);
}
