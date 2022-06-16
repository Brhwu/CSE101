/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA3
* Graph.c
* Implementation file for Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"
#define NIL -1
#define UNDEF -2


/*** Private GraphObj type ***/

typedef struct GraphObj {
   List* adj;
   int time;
   int order;
   int size;
   int* parent;
   int* discover;
   int* finish;
   int* color;
} GraphObj;

enum colors{white, gray, black};

/*** Constructors-Destructors ***/
// Graph newGraph()
// returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n) {
   Graph G = malloc(sizeof(GraphObj));
   G->adj = malloc(sizeof(List) * (n+1));
   G->parent = malloc(sizeof(int) * (n+1));
   G->discover = malloc(sizeof(int) * (n+1));
   G->finish = malloc(sizeof(int) * (n+1));
   G->color = malloc(sizeof(int) * (n+1));
   for(int i = 0; i < n+1; ++i) {
      G->adj[i] = newList();
      G->parent[i] = NIL;
      G->discover[i] = G->finish[i] = UNDEF;
   }
   G->order = n;
   G->size = 0;
   return(G);
}

// freeGraph()
// frees all heap memory associated with the Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG) {
   if(pG != NULL && *pG != NULL) { 
      for(int i = 0; i < (getOrder(*pG)+1); ++i) {
         freeList(&(*pG)->adj[i]);
      }
      free((*pG)->adj);
      free((*pG)->parent);
      free((*pG)->discover);
      free((*pG)->finish);
      free((*pG)->color);
      free(*pG);
      *pG = NULL;
   }
}


/*** Access functions ***/
// int getOrder()
// returns the order(number of vertices) in G
int getOrder(Graph G) {
   if(G == NULL) {
      printf("Graph Error: getOrder called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->order);
}

// int getSize()
// returns the size(number of edges) in G
int getSize(Graph G) {
   if(G == NULL) {
      printf("Graph Error: getSize called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->size);
}

// int getParent()
// return the parent of vertex u in the DFS tree created by DFS(), or NIL if DFS() has not yet been called
// pre 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
   if(G == NULL) {
      printf("Graph Error: getParent called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if(1 > u || u > getOrder(G)) {
      printf("Graph Error: invalid vertex number\n");
      exit(EXIT_FAILURE); 
   }
   return(G->parent[u]);
}


// getDiscover()
// returns the discover time
/* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u) {
   if(G == NULL) { 
      printf("Graph Error: getDiscover called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if(1 > u || u > getOrder(G)) {
      printf("Graph Error: invalid vertex number\n");
      exit(EXIT_FAILURE);
   }
   return(G->discover[u]);

}


// getFinish()
// returns the finish time
/* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u) { 
   if(G == NULL) { 
      printf("Graph Error: getFinish called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if(1 > u || u > getOrder(G)) {
      printf("Graph Error: invalid vertex number\n");
      exit(EXIT_FAILURE);
   }
   return(G->finish[u]);

}

/*** Manipulation procedures ***/

// void addArc()
// inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)
// precondition that their two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v) {
   if(G == NULL) { 
      printf("Graph Error: addArc called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)) {
      printf("Graph Error: addArc called with invalid u\n");
      exit(EXIT_FAILURE);
   }
   int k = 1;
   moveFront(G->adj[u]);
   while(index(G->adj[u]) != -1) {
      if(get(G->adj[u]) == v) {
         ++k;
      }
      moveNext(G->adj[u]);
   }

   if(k == 1) { //start
      moveFront(G->adj[u]);
      while(index(G->adj[u]) != -1 && get(G->adj[u]) < v) { //index start until end or is less than v
         moveNext(G->adj[u]);
      }
   if(index(G->adj[u]) == -1) { 
      append(G->adj[u], v);
   }
   else {
      insertBefore(G->adj[u], v);
   }
   G->size++;
   }
}


// void addEdge()
// inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u
// precondition that their two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v) {
   if(G == NULL) {
      printf("Graph Error: addEdge called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if(u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)) {
      printf("Graph Error: addEdge called with invalid u\n");
      exit(EXIT_FAILURE);
   }
   if(u != v) { // uses addArc as it is addEdge but one way
      addArc(G, u, v);
      addArc(G, v, u);
      G->size--;
   }
}



// void visit()
// helper function for DFS()
void visit(Graph G, List S, int x) { // based on pseudocode visit in GraphAlgorithms on class website
   enum colors wh = white;
   enum colors gr = gray;
   enum colors bl = black;

   G->discover[x] = ++(G->time); 
   G->color[x] = gr;
   moveFront(G->adj[x]);
   int y;

   while(index(G->adj[x]) > -1) {
         y = get(G->adj[x]);
         if(G->color[y] == wh) {
            G->parent[y] = x;
            visit(G, S, y);
         }
         moveNext(G->adj[x]);
   }
   G->color[x] = bl;

   G->finish[x] = ++(G->time);
   prepend(S, x);
}




// void DFS()
// performs the depth first search algorithm on G
void DFS(Graph G, List S) {  // based on pseudocode DFS in GraphAlgorithms on class website
   if(G == NULL) {
      printf("Graph Error: DFS called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }

   if(S == NULL) {
      printf("List Error: DFS called with NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(S) != getOrder(G)) {
      printf("List Error: length of List is not equal to Graph order\n");
      exit(EXIT_FAILURE);
   }

 
   enum colors wh = white;	
   for(int i = 0; i < getOrder(G)+1; ++i) { //for all x in V(G)
      G->color[i] = wh;
      G->parent[i] = NIL;
   }
   G->time = 0;
   List T = copyList(S);  //get the order of verticies for 5-7 so S can be edited in visit 
   clear(S);
   moveFront(T);
   while(index(T) != -1) {  //defines the order in which vertices are to be processed in the main loop (5-7) of DFS
      if((G->color[(get(T))]) == wh) {
	      visit(G, S, get(T));
      }
      moveNext(T);
   }
   freeList(&T);

}


   


/*** Other operations ***/
// Graph transpose()
// returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G) {
   if(G == NULL) {
      printf("Graph Error: transpose called with NULL Graph reference");
      exit(EXIT_FAILURE);
   }
   Graph T = newGraph(getOrder(G));
   for(int i = 1; i < getOrder(G)+1; ++i) {
      for(moveFront(G->adj[i]); index(G->adj[i])>=0; moveNext(G->adj[i])) {
         addArc(T, (get(G->adj[i])), i);
      }
   }
   return(T);
}

// Graph copyGraph()
// returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G) {
   if(G == NULL) {
      printf("Graph Error: printGraph called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   Graph C = newGraph(G->order);
   for(int i = 0; i < (getOrder(G) + 1); ++i) {
      C->adj[i] = copyList(G->adj[i]);
      C->parent[i] = G->parent[i];
      C->discover[i] = G->discover[i];
      C->finish[i] = G->finish[i];
   }
   C->order = G->order;
   C->size = G->size;
   return(C);

}


// void printGraph()
// prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G) { 
   if(G == NULL) {
      printf("Graph Error: printGraph called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   for(int i = 1; i < getOrder(G)+1; ++i) {
      fprintf(out, "%d:", i);
      moveFront(G->adj[i]);
      while(index(G->adj[i]) != -1) {
         fprintf(out, " %d", get(G->adj[i]));
         moveNext(G->adj[i]);
      }
      fprintf(out, "\n");
   }
}
