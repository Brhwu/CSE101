/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA5
* List.cpp
* Implementation file for List ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"


// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List() {
   frontDummy = new Node(0);
   frontDummy->prev = nullptr;
   backDummy = new Node(0);
   backDummy->next = nullptr;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
}

   // Copy constructor.
List::List(const List& L) {
   // make this an empty List
   frontDummy = new Node(0);
   frontDummy->prev = nullptr;
   backDummy = new Node(0);
   backDummy->next = nullptr;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;


   this->moveFront();
   Node* N = L.frontDummy->next;
   while (N != L.backDummy) {
	   this->insertAfter(N->data);
	   moveNext();
	   N = N->next;
   }
}

// Destructor
List::~List(){
   Node* N = frontDummy;
   while(N != backDummy) {
	   Node* temp = N->next;
	   delete N;
	   N = temp;
   }
   delete backDummy;
}


// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
   return(num_elements);
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
   if(num_elements<=0) {
      throw std::length_error("List: front(): empty list");
   }
   return(frontDummy->next->data);
}



// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
   if(num_elements<=0) {
      throw std::length_error("List: back(): empty list");
   }
   return(backDummy->prev->data);
}


// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
   return(pos_cursor);
}


// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
   if(pos_cursor >= num_elements) {
      throw std::range_error("List: peekNext(): cursor at back");
   }
   return(afterCursor->data);
}


// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
   if(pos_cursor <= 0) {
      throw std::range_error("List: peekPrev(): cursor at front");
   }
   return(beforeCursor->data);
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
   pos_cursor = 0;
   moveFront();
   while(num_elements > 0) {
      eraseAfter();
   }
}


// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
   pos_cursor = 0;
   beforeCursor = frontDummy;
   afterCursor = frontDummy->next;
}
   

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
   pos_cursor = num_elements;
   afterCursor = backDummy;
   beforeCursor = backDummy->prev;
}


// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext() {
   if(pos_cursor >= num_elements) {
      throw std::range_error("List: moveNext(): cursor at back");  
   }
   pos_cursor++;
   afterCursor = afterCursor->next;
   beforeCursor = afterCursor->prev;
   return(beforeCursor->data);
}


// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev() {
   if(pos_cursor <= 0) {
      throw std::range_error("List: movePrev(): cursor at front");
   }
   pos_cursor--;
   beforeCursor = beforeCursor->prev;
   afterCursor = beforeCursor->next;
   return(afterCursor->data);
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
   Node* N = new Node(x);

   if(num_elements == 0) {
      frontDummy->next = N;
      backDummy->prev = N;
      N->next = backDummy;
      N->prev = frontDummy;
      
      beforeCursor->next = N;
      afterCursor = N;

   }
   else {
      N->next = afterCursor;
      N->prev = beforeCursor;
      afterCursor->prev = N;
      beforeCursor->next = N;
      afterCursor = N;

   }
   num_elements++;
}




// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
   Node* N = new Node(x);
	
   if(num_elements == 0) {
      frontDummy->next = N;
      backDummy->prev = N;
      N->next = backDummy;
      N->prev = frontDummy;

      beforeCursor->next = N;
      afterCursor->prev = N; 
      beforeCursor = N;
      
   }
   else {
      N->next = afterCursor;
      N->prev = beforeCursor;
      beforeCursor->next = N;
      afterCursor->prev = N;
      beforeCursor = N;
   }
   num_elements++;
   pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
   if(pos_cursor >= num_elements) {
      throw std::range_error("List: setAfter(): cursor at back");
   }
   afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
   if(pos_cursor <= 0) {
      throw std::range_error("List: setBefore(): cursor at front");
   }
   beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
   if(pos_cursor >= num_elements) {
      throw std::range_error("List: eraseAfter(): cursor at back");
   }
   Node* N = afterCursor;  
   if(num_elements > 1) {
      afterCursor = afterCursor->next;
      afterCursor->prev = beforeCursor;
      beforeCursor->next = afterCursor;
      num_elements--;
      delete N;
   }
   else {
      if(afterCursor != backDummy) {
     
      frontDummy->next = backDummy;
      backDummy->prev = frontDummy;
      afterCursor = backDummy;
      afterCursor->prev = beforeCursor;
      beforeCursor->next = afterCursor;
      num_elements--;
      delete N;
   }
   }
}


// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
   if(pos_cursor <= 0) {
      throw std::range_error("List: eraseBefore(): cursor at front");  
   }
   Node* N = beforeCursor;
   
   beforeCursor = beforeCursor->prev;
   beforeCursor->next = afterCursor;
   afterCursor->prev = beforeCursor;
   num_elements--;
   pos_cursor--;
   delete N;
}




// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x) {
   Node* N = afterCursor;
   while(N != backDummy) {
      if(N->data == x) {
         beforeCursor = N;
         afterCursor = N->next;
         pos_cursor++;
         return(pos_cursor);
      }
      N = N->next;
      pos_cursor++;
   }
   return(-1);
}



// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x) {
   Node* N = beforeCursor;
   while(N != frontDummy) {
      if(N->data == x) {
         afterCursor = N;
         beforeCursor = N->prev;
	 pos_cursor--;
         return(pos_cursor);
      }
      N = N->prev;
      pos_cursor--;
   }
   pos_cursor = 0;
   return(-1);
}




// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {  //if dup iterms before cursor minus it
   Node* N = frontDummy->next;  
   int Cstore = pos_cursor;
   int counterN = 1;
   int counterX;
   int dis = 0;
   moveFront();
   while(N != backDummy) {
      counterX = 1;
      Node* X = N->next;
      while(X != backDummy) {
         if(N->data == X->data) {
            Node* T = X->prev;
	    dis = counterN + counterX;
	    if(dis <= Cstore) {
               Cstore--;
	    }
	    dis = 0;
	    T->next = X->next;
	    X->next->prev = T;
	    delete(X);
	    X = T;
	    num_elements--;
	    counterX--;
	 }
         counterX++;
         X = X->next;
	 }
      N = N->next;
      counterN++;
   }
   for(int i = 0; i<Cstore; i++) {
      moveNext();
   }
}




// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const { 
   List J;
   Node* N = this->frontDummy->next;
   while(N != this->backDummy) {
      J.insertBefore(N->data);
      N = N->next;
   }
   Node* M = L.frontDummy->next;
   while(M != L.backDummy) {
      J.insertBefore(M->data);
      M = M->next;
   }
   J.moveFront();

   return J;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {  
   Node* N = nullptr;
   std::string s = "(";
   for(N=frontDummy->next; N!=backDummy; N=N->next) {
      s += std::to_string(N->data);
      if(N->next != backDummy) {
         s += ", ";
      }
   }
   s += ")";
   
   return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;

   eq = (this->num_elements == R.num_elements);
   N = this->frontDummy->next;
   M = R.frontDummy->next;
   while(eq && N!=backDummy) {
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<(std::ostream& stream, const List& L) {
   return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==(const List& A, const List& B) {
   return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=(const List& L) {
   if(this != &L) { 
      List temp = L;
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(num_elements, temp.num_elements);
      std::swap(pos_cursor, temp.pos_cursor);
   }
 
   return *this;
}

