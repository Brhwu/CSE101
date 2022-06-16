/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA3
* GraphTest.c
* Test file for Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   int i, n=10;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,5);  // duplicate test
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   addArc(G, 9,5);
   addArc(G, 10,10); //duplicate stress test 
   addArc(G, 10,10);
   addArc(G, 10,10);
   addArc(G, 10,10);
   addArc(G, 10, 1);
   addArc(G, 10, 2);
   addArc(G, 2, 10);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");






   // get total number of strong connected components
   int c = 0;
   moveFront(S);
   while(index(S) != -1) {
      if(getParent(G, get(S)) == NIL) {
         ++c;
      }
   moveNext(S);
   }


   fprintf(stdout, "\n");
   fprintf(stdout, "G contains %d strongly connected components:", c);

   // get strongly connect components
   int x = 0;  // used to list components (1, 2, ect)
   moveBack(S); // pop off stack
   while(index(S) != -1) {
      ++x;
      fprintf(stdout, "\n");
      fprintf(stdout, "Component %d: ", x);
      int y = 0;
      while(y != -1) {  // count how far cursor goes back
         ++y;
         if(getParent(G, get(S)) == NIL) { // if there is a strong connected component (NIL)
            break;
         }
         movePrev(S);
         if(index(S) == -1) {  // if at end of List
            moveFront(S);
            break;
         }
      }

      fprintf(stdout, "%d ", get(S));  // prints first SCC
      for(int k = 0; k < y - 1; ++k) {  // go forward (minus 1 since first is printed)
         moveNext(S);
         fprintf(stdout, "%d ", get(S));  //
      }

      for(int k = 0; k < y; ++k) {  // go back to original position in List
         movePrev(S);
      }
   }

   fprintf(stdout, "\n");


   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}
