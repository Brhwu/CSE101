/*********************************************************************************
* Brandon Hwu, brhwu
* 2022 Spring CSE101 PA7
* Dictionary.cpp
* Implementation file for Dictionary ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include"Dictionary.h"



// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const { // based on BST pseudocode InOrderTreeWalk
   if(R != nil) { 
      inOrderString(s, R->left);
      s += R->key;
      s += " : ";
      s += std::to_string(R->val);
      s += "\n";
      inOrderString(s, R->right);
   }
}


// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const { // based on BST pseudocode PreOrderTreeWalk  
   if(R != nil) { 
      s += R->key;
      s += "\n";
      preOrderString(s, R->left);
      preOrderString(s, R->right);
   }
}


// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) { // based on BST pseudocode PreOrderTreeWalk
   if(R != nil && N != R) {
      this->setValue(R->key, R->val);
      preOrderCopy(R->right, N);
      preOrderCopy(R->left, N);
   }
}
      




// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) { // based on BST pseudocode PostOrderTreeWalk
   if(R != nil) {
      postOrderDelete(R->left);
      postOrderDelete(R->right);
      delete R;
   }
}

   

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {  // based on BST pseudocode TreeSearch
   if(R == nil || k == R->key) {
      return R;
   }
   else if(k < R->key) {
      return search(R->left, k);
   }
   else {
      return search(R->right, k);
   }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {  // based on BST pseudocode TreeMinimum
   while(R->left != nil) {  
      R = R->left;
   }
   return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {  // based on BST pseudocode TreeMaximum
   while(R->right != nil) {  
      R = R->right;
   }
   return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N) {  // based on BST pseudocode TreeSuccessor
   if(N->right != nil) { 
      return findMin(N->right);
   }
   Node* Y = (N->parent);
   while(Y != nil && N == Y->right) {
      N = Y;
      Y = Y->parent;
   }
   return Y;
}


// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {  // based on BST pseudocode TreePredecessor
   if(N->left != nil) { 
      return findMax(N->left);
   }
   Node* Y = (N->parent);
   while(Y != nil && N == Y->left) {
      N = Y;
      Y = Y->parent;
   }
   return Y;
}


// transplant()
// Replaces one subtree as a child of its parent with another subtree
// Added helper function.
void Dictionary::transplant(Node* U, Node* V) { // based on BST pseudocode Transplant
   if(U->parent == nil) { 
      root = V;
   }
   else if(U == U->parent->left) {
      U->parent->left = V;
   }
   else {
      U->parent->right = V;
   }
   if(V != nil) {  
      V->parent = U->parent;
   }
}


// Delete()
// Deletes Z from the subtree
// Added helper function
void Dictionary::Delete(Node* Z) {  // based on BST pseudocode Delete
   if(Z->left == nil) {
      transplant(Z, Z->right);
   }
   else if(Z->right == nil) {
      transplant(Z, Z->left);
   }
   else {
      Node* Y = findMin(Z->right);
      if(Y->parent != Z) {
         transplant(Y, Y->right);
	 Y->right = Z->right;
	 Y->right->parent = Y;
      }
      transplant(Z, Y);
      Y->left = Z->left;
      Y->left->parent = Y;
   }
   delete Z;
}

// Private Constructor --------------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v){
   key = k;
   val = v;
   parent = nullptr; 
   left = nullptr;
   right = nullptr;
}



// Class Constructors & Destructors ----------------------------------------
   
// Creates new Dictionary in the empty state. 
Dictionary::Dictionary() {
   nil = new Node("thisisnull", 0);
   nil->parent = nil;
   nil->left = nil;
   nil->right = nil;
   root = nil;  
   current = nil;
   num_pairs = 0;
}

   

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
   nil = new Node("thisisnull", 0);
   nil->parent = nil;
   nil->left = nil;
   nil->right = nil;
   root = nil; 
   current = nil;
   num_pairs = 0;
   
   this->preOrderCopy(D.root, D.nil);  
}

// Destructor
Dictionary::~Dictionary() {
   postOrderDelete(root); 
   delete nil;
}


// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
   return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
   if(search(root, k) != nil) {
      return true;
   }
   return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
   Node* S = search(root, k);
   if(S == nil) {
      std::string q = "\"";
      throw std::logic_error("Dictionary: getValue(): key " + q + k + q + " does not exist");
   }

   return(S->val);
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
   if(current != nil) {
      return true;
   }
   return false;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
   if(hasCurrent() == false) {
      throw std::logic_error("Dictionary: currentKey(): current undefined");
   }
   return(current->key);
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
   if(hasCurrent() == false) {
      throw std::logic_error("Dictionary: currentVal(): current undefined");
   }
   return(current->val);
}



// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
   postOrderDelete(root);
   num_pairs = 0;
   current = nil;
   root = nil;
}   

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {  // based on BST pseudocode TreeInsert
   Node* Z = new Node(k, v);
   Z->right = nil;
   Z->left = nil;
   Z->parent = nil;
   Node* Y = nil;
   Node* X = root;
   while(X != nil) {
      Y = X;
      if(k == X->key) {
         X->val = v;
	 delete Z;
	 return;
      }
      else if(Z->key < X->key) {
         X = X->left;
      }
      else {
         X = X->right;
      }
   }
   Z->parent = Y;
   if(Y == nil) {
      root = Z;
   }
   else if(Z->key < Y->key) {
      Y->left = Z;
   }
   else {
      Y->right = Z;
   }
   num_pairs++;     
}
   

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
   Node* D = search(root, k);
   if(D == nil) {  
      std::string q = "\"";
      throw std::logic_error("Dictionary: remove(): key " + q + k + q + " does not exist");
   }
   if(current->key == k) {
      current = nil; 
   }
   Delete(D);
   num_pairs--;
}




// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() { //might need precond
   current = findMin(root);  //def not current
}



// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() { //might need precond
   current = findMax(root);  //def not current
}




// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() { //successor  //helper clash
   if(hasCurrent() == false) {
      throw std::logic_error("Dictionary: next(): current not defined");
   }
   current = findNext(current);
}


// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
   if(hasCurrent() == false) {
      throw std::logic_error("Dictionary: prev(): current not defined");
   }
   current = findPrev(current);
}



// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
   std::string s;
   inOrderString(s, root); 
   return s;
}
   

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
   std::string s;
   preOrderString(s, root); 
   return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
   std::string t;
   std::string d;
   t = this->to_string();
   d = D.to_string();
   if(t == d) {
      return true;
   }
   return false;
}


// Overloaded Operators ----------------------------------------------------
   
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
   return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
   return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
   if(this != &D) {
      Dictionary temp = D;
      std::swap(nil, temp.nil);
      std::swap(root, temp.root);
      std::swap(current, temp.current);
      std::swap(num_pairs, temp.num_pairs);
   }
   return *this;
}

