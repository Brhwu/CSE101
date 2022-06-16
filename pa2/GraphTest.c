/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA2
* GraphTest.c
* File to test Graph.c functions.
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]) {
	
	Graph G = NULL;

	int n = 10;

	G = newGraph(n);
   for(int i=2; i<n; i++){
      addEdge(G, 1, i);
   }

    printGraph(stdout, G);

    makeNull(G);


    addEdge(G, 2, 2); //going to itself that is not supposed to show up 
    addArc(G, 3, 8);
    addEdge(G, 3, 7);
    addArc(G, 3, 8);
    addArc(G, 5, 10); //one sided

    printGraph(stdout, G);

    freeGraph(&G);

    //getOrder(G);

    G = newGraph(n);

    addEdge(G, 3, 8);

    printGraph(stdout, G);
    printf("\n");
    Graph A = newGraph(100);
    List L = newList();
    addEdge(A, 64, 4);
    addEdge(A, 64, 3);
    addEdge(A, 42, 2);
    addEdge(A, 2, 64);
    addEdge(A, 4, 2);
    addEdge(A, 3, 42);
    BFS(A, 3);
    getPath(L, A, 64);
    printList(stdout, L);

    printGraph(stdout, A);

    return(0);
}
