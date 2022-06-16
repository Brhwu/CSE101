/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA2
* Graph.c
* Implementation file for Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"
#define NIL -1
#define INF -2


/*** Private GraphObj type ***/

typedef struct GraphObj {
   List* adj;
   int source;
   int order;
   int size;
   int* parent;
   int* dist;
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
   G->dist = malloc(sizeof(int) * (n+1));
   G->color = malloc(sizeof(int) * (n+1));
   for(int i = 0; i < n+1; ++i) {
      G->adj[i] = newList();
      G->parent[i] = NIL;
      G->dist[i] = INF;
   }
   G->order = n;
   G->size = 0;
   G->source = NIL;
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
      free((*pG)->dist);
      free((*pG)->color);
      free(*pG);
      *pG = NULL;
   }
}


/*** Access functions ***/
// int getOrder()
// returns the order
int getOrder(Graph G) {
   if(G == NULL) {
      printf("Graph Error: getOrder called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->order);
}

// int getSize()
// returns the size
int getSize(Graph G) {
   if(G == NULL) {
   printf("Graph Error: getSize called with NULL Graph reference\n");
   exit(EXIT_FAILURE);
   }
   return(G->size);
}

// int getSource()
// returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called
int getSource(Graph G) {
   if(G == NULL) {
      printf("Graph Error: getSource called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   return(G->source);
}

// int getParent()
// return the parent of vertex u in the BFS tree created by BFS(), or NIL if BFS() has not yet been called
// pre 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
   if(G == NULL) {
      printf("Graph Error: getParent called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if(1 > u && u > getOrder(G)) {
      printf("Graph Error: invalid vertex number\n");
      exit(EXIT_FAILURE); 
   }
   return(G->parent[u]);
}


// int getDist()
// returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called
// 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
   if(G == NULL) {
      printf("Graph Error: getDist called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if(1 > u && u > getOrder(G)) {
      printf("Graph Error: invalid vertex number\n");
      exit(EXIT_FAILURE); 
   }
   return(G->dist[u]);
}


// void getPath()
// appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if
// no such path exists
// has the precondition getSource(G)!=NIL, so BFS() must be called before getPath() is called
// 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u) {  // based on pseudocode printPath in GraphAlgorithms on class website
   if(G == NULL) {
      printf("Graph Error: getPath called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if(L == NULL) {
      printf("Graph Error: getDist called with NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(1 > u && u > getOrder(G)) {
      printf("Graph Error: getPath called with invalid u\n");
      exit(EXIT_FAILURE);
   }
   if(getSource(G) == NIL) {
      printf("Graph Error: BFS must be called\n");
      exit(EXIT_FAILURE);
   }
   if(u == getSource(G)) {
      append(L, u);
   }
   else if(getParent(G, u) == NIL) {
      append(L, NIL);
   }
   else {
      getPath(L, G, getParent(G, u));
      append(L, u);
   }
}


/*** Manipulation procedures ***/
// void makeNull()
// deletes all edges of G, restoring it to its original (no edge) state
void makeNull(Graph G) {
   if(G == NULL) {
      printf("Graph Error: makeNull called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   for(int i = 0; i < getOrder(G)+1; ++i) {
      clear(G->adj[i]);
      G->parent[i] = NIL;
      G->dist[i] = INF;
   }
   G->size = 0;
   G->source = NIL;
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
   if(u != v) {
      moveFront(G->adj[u]);
      while(index(G->adj[u]) != -1 && get(G->adj[u]) < v) {
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

// void BFS()
// runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s) {  // based on pseudocode BFS in GraphAlgorithms on class website
   if(G == NULL) {
      printf("Graph Error: BFS called with NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if(s < 1 || getOrder(G) < s) {
      printf("Graph Error: BFS called with invalid s\n");
      exit(EXIT_FAILURE);
   }
   G->source = s;
   enum colors wh = white;
   enum colors gr = gray;
   enum colors bl = black;	
   for(int i = 0; i < getOrder(G)+1; ++i) {
      G->color[i] = wh;
      G->dist[i] = INF;
      G->parent[i] = NIL;
   }
   G->color[s] = gr;
   G->dist[s] = 0;
   G->parent[s] = NIL;
   List Q = newList();
   append(Q, s);
   while(length(Q) != 0) {
      int x = front(Q);
      deleteFront(Q);
      moveFront(G->adj[x]);
      while(index(G->adj[x]) != -1) {
         int y = get(G->adj[x]);
         if(G->color[y] == wh) {
            G->color[y] = gr;
            G->dist[y] = G->dist[x] + 1;
            G->parent[y] = x;
            append(Q, y);
         }
         moveNext(G->adj[x]);
      }
      G->color[x] = bl;
   }
   freeList(&Q);
}


/*** Other operations ***/
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
