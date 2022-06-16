/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA3
* List.c
* Implementation file for List ADT
*********************************************************************************/
#include<stdio.h>  
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"


// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node; //altered from Queue.c

// private NodeObj type
typedef struct NodeObj{ //altered from Queue.c
   ListElement data;  
   Node next;
   Node prev;  
} NodeObj;

// private ListObj type
typedef struct ListObj{  //altered from queue.c
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------


// List newList(void)
// Creates and returns a new empty List.
List newList(void) { //based on newQueue in queue.c
	List L;
	L = malloc(sizeof(ListObj));
	assert( L!=NULL);
	L->front = L->back = NULL;
	L->length = 0;
	L->index = -1; 
	return(L);
} 


// newNode() Used as a helper function
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data) { //based on newNode from queue.c
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->next = NULL;
   return(N);
}

// freeNode() Used as a helper function
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN) {  //based on freeNode from queue.c
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){  //based on freeQueue from queue.c
   if(pL!=NULL && *pL!=NULL) {
      while(length(*pL) != 0) { 
         deleteFront(*pL);  
      }
      free(*pL);
      *pL = NULL;
   }
}




// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L) { 
   if(L==NULL) {  //based on getLength from queue.c
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}



// index()
// Return index of cursor element if defined, -1 otherwise.
int index(List L) { //based on getLength from queue.c
   if(L == NULL) {
      printf("List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->index); //since cursor is not defined it is -1
}


// front()
// Returns front element of L. 
// Pre: length()>0  
int front(List L) {  //based on getFront from queue.c
   if(L==NULL) {
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->length <= 0) {  //pre
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}

// back()
// Returns back element of L. 
// Pre: length()>0
int back(List L) { //based on getFront from queue.c
   if(L==NULL) {
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->length <= 0) {  //pre
      printf("List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data);
}

// get()
// Returns cursor element of L. 
// Pre: length()>0, index()>= 0
int get(List L){ //based on getFront from queue.c
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L) <= 0 && index(L) < 0){ //pre
      printf("List Error: calling get() on an empty List\n");
      exit(EXIT_FAILURE);
   }   
   return(L->cursor->data);
}

// equals()
// Returns true if Lists A and B are in same
// state, and returns false otherwise.
bool equals(List A, List B) { //based on equals from queue.c
   if (A == NULL || B == NULL) {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   bool eq;
   Node N, M;
   eq = (A->length == B->length);
   N = A->front;
   M = B->front;
   while (eq && N!=NULL) {
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) { 
   if(L==NULL) {
      printf("List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   while(length(L) != 0) {
	   deleteFront(L);
   }
   L->cursor = NULL;
   L->index = -1;
}

// set()
// Overwrites the cursor element if defined, -1 otherwise.
void set(List L, int x) {
   if(L==NULL) {
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L) > 0 && index(L)>=0) { //if cursor is defined
      L->cursor->data = x;
   }
   L->cursor->data = -1;
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
   if(L==NULL) {
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   L->cursor = L->front;
   if(L->length != 0) { //if non-empty
	   L->index = 0;
   }
}

// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) { 
   if(L==NULL) {
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   L->cursor = L->back;
   L->index = L->length - 1;
}


// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) { 
   if(L == NULL) {
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor != NULL) { //if cursor is defined
      L->cursor = L->cursor->prev;
      L->index--;
   }
}

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) { 
   if(L == NULL) {
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor != NULL) {  //if cursor is defined
      L->cursor = L->cursor->next;
      if(L->cursor != NULL) {
         L->index++;
      }
      else {  //cursor is at back/do nothing (already undefined)
         L->index = -1;
      }
   }
}


// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x) { //based on Enqueue from queue.c
   Node N = newNode(x);
   if(L==NULL) {
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L)==0) { //if non empty 
      L->front = L->back = N;
   }
   else{
      N->next = L->front;
      L->front->prev = N;
      L->front = N;
      if(index(L) >= 0) {
         L->index++;
      }
   }
   L->length++;
}


// append()
// Insert new element into L. If L is non-empty,
// insertion takes place before back element.
void append(List L, int x) { //based on Enqueue from queue.c
   Node N = newNode(x);
   if(L==NULL) {
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L) == 0) {  //if empty
      L->front = L->back = N;
   }
   else {  //if non-empty
      N->prev = L->back;
      L->back->next = N;
      L->back = N;
   }
   L->length++;
}



// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
   Node N = newNode(x);
   if(L==NULL) {
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L)<=0 && index(L)<0) { //pre
      printf("List Error: calling insertBefore() with an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor == L->front) { //if cursor is at front
      N->next = L->front;
      L->front->prev = N;
      L->front = N;
   }
   else { //if cursor is anywhere except front
      N->prev = L->cursor->prev;
      N->next = L->cursor;
      L->cursor->prev->next = N;
      L->cursor->prev = N;
   }
   L->index++;
   L->length++;
}


// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
   Node N = newNode(x);
   if(L==NULL) {
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L)<=0 && index(L)<0) { //pre
      printf("List Error: calling insertAfter() with an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   if(L->cursor == L->back) { //if cursor is at back
      N->prev = L->back;
      L->back->next = N;
      L->back = N;
   }
   else {
      N->next = L->cursor->next;
      N->prev = L->cursor;
      L->cursor->next->prev = N;
      L->cursor->next = N;
   }
   L->length++;
}


// deleteFront()
// Deletes data at front of Q.
// Pre: length()>0
void deleteFront(List L){  //based on Dequeue in queue.c
   Node N = NULL;

   if(L==NULL) {
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L) <= 0) { //pre
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   N = L->front;
   if(length(L) > 0) { 
      L->front = L->front->next;
   }
   else {
      L->front = L->back = NULL;
   }
   L->index--;  //index will go down no matter where cursor is
   L->length--;
   freeNode(&N);
}


// deleteBack()
// Deletes data at back of L.
// Pre: length()>0
void deleteBack(List L){ //based on Dequeue in queue.c
   Node N = NULL;
   if(L==NULL) {
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(length(L) <= 0) { //pre
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   N = L->back;
   if(length(L) == 1) { //if L has one element
      L->front = L->back = L->cursor = NULL;
      L->index = -1;
   }
   else{
      if(index(L) == (length(L)-1)) { //if cursor is on back of L and L has 2 or more elements
         L->cursor = NULL;
	 L->index = -1;
      }
      L->back = L->back->prev;
      L->back->next = NULL;
   }
  L->length--; 
  freeNode(&N);
}


// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) { 
   Node N = NULL;
   if(L==NULL) {
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   if(length(L) <= 0 && index(L) < 0) { //pre
      printf("List Error: calling delete() with a NULL cursor\n");
      exit(1);
   }
   N = L->cursor;
   L->cursor = NULL;
   if(L->length == 1) { //if L has one element
      freeNode(&L->front);
      L->front = L->back = NULL;
   }
   else if(L->front == N) { //if cursor at front of L
      N = L->front;
      L->front = L->front->next;
      freeNode(&N);
      L->front->prev = NULL;
   }
   else if(L->back == N) { //if cursor at back of L
      N = L->back;
      L->back = L->back->prev;
      freeNode(&N);
      L->back->next = NULL;
   }
   else { //cursor anywhere on L except front and back
      N->prev->next = N->next;
      N->next->prev = N->prev;
      freeNode(&N);
   }
   L->length--;
   L->index = -1;
}



// Other operations -----------------------------------------------------------


// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L) { //based on queue.c function printQueue
   Node N = NULL;
   if(L==NULL){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   for(N = L->front; N != NULL; N = N->next) {
      fprintf(out, "%d ", N->data);
   }
}




// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) { 
   List C = newList();
   Node N = NULL;
   if(L==NULL) {
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   N = L->front;
   while(N != NULL) {
      append(C, N->data);
      N = N->next;
   }
   return(C);
}
