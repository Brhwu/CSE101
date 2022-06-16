/********************************************************************************* 
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA3
* Graph.h 
* Header file for Graph ADT 
*********************************************************************************/
#include "List.h"
#define NIL -1
#define UNDEF -2

/*** Exported types ***/

typedef int ListElement;
typedef struct ListObj* List;
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

Graph newGraph(int n);

void freeGraph(Graph* pG);

/*** Access functions ***/

int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);


/*** Manipulation procedures ***/

void addArc(Graph G, int u, int v);

void addEdge(Graph G, int u, int v);

void DFS(Graph G, List S);

/*** Other operations ***/

Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);
