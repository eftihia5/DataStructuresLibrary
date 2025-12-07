#include "avltree.h"
#include <iostream>

//Κατασκευαστής για την κλάση AVLTree
AVLTree::AVLTree() : root(nullptr) {}
//Δημιουργία νέου κόμβου
AVLTree::Node *AVLTree::newNode(int key) {
  Node *node = new Node(); //Δημιουργία νέου κόμβου δυναμικά
  node->key = key;         //Αρχικοποίηση του key
  node->left = nullptr; //Αρχικοποίηση του αριστερού παιδιού
  node->right = nullptr; //Αρχικοποίηση του δεξιού παιδιού
  node->height = 1; //Αρχικοποίηση του ύψους
  return node;
}

//Εκτέλεση δεξιάς περιστροφής
AVLTree::Node *AVLTree::rightRotate(Node *y) {
  Node *x = y->left; //Αποθήκευση του αριστερού παιδιού
  Node *T2 = x->right; //Αποθήκευση του δεξιού παιδιού
  x->right = y;        //Ανανέωση του δεξιού παιδιού
  y->left = T2; //Ανανέωση του αριστερού παιδιού
  y->height = max(height(y->left), height(y->right)) +
              1; //Ενημέρωση του ύψους του κόμβου y
  x->height = max(height(x->left), height(x->right)) +
              1; //Ενημέρωση του ύψους του κόμβου x
  return x;
}

//Εκτέλεση αριστερής περιστροφής
AVLTree::Node *AVLTree::leftRotate(Node *x) {
  Node *y = x->right; //Αποθήκευση του δεξιού παιδιού
  Node *T2 = y->left; //Αποθήκευση του αριστερού παιδιού
  y->left = x;   //Ανανέωση του αριστερού παιδιού
  x->right = T2; //Ανανέωση του δεξιού παιδιού
  x->height = max(height(x->left), height(x->right)) +
              1; //Ενημέρωση του ύψους του κόμβου x
  y->height = max(height(y->left), height(y->right)) + 1;
  return y; //Ενημέρωση του ύψους του κόμβου y
}

//Επιστροφή του ύψους του κόμβου
int AVLTree::height(Node *N) {
  if (N == nullptr)
    return 0;
  return N->height;
}

//Επιστροφή του μέγιστου από τους δύο αριθμούς
int AVLTree::max(int a, int b) { return (a > b) ? a : b; }

//Επιστροφή του συντελεστή ισορροπίας του κόμβου
int AVLTree::getBalanceFactor(Node *N) {
  if (N == nullptr)
    return 0;
  return height(N->left) - height(N->right);
}

//Εισαγωγή νέου κόμβου στο δένδρο
AVLTree::Node *AVLTree::insertNode(Node *node, int key) {
  //Αν ο κόμβος είναι null, δημιουργεί έναν νέο κόμβο και τον επιστρέφει
  if (node == nullptr)
    return newNode(key);
    //Εισάγει αναδρομικά το νέο κόμβο στο κατάλληλο υποδένδρο
  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

    //Ενημέρωση ύψους του κόμβου
  node->height = 1 + max(height(node->left), height(node->right));

    //Ελέγχει αν ο κόμβος είναι ισορροπημένος
  int balanceFactor = getBalanceFactor(node);

   
    
  //Αν ο κόμβος δεν είναι ισορροπημένος τοτε:  
  if (balanceFactor > 1) {
     //Πρώτη περίπτωση:Αριστερή-Αριστερή
    if (key < node->left->key)
      return rightRotate(node);
       //Δεύτερη περίπτωση:Αριστερή-Δεξιά
    else if (key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  
  if (balanceFactor < -1) {
     //Τρίτη περίπτωση:Δεξιά-Δεξιά
    if (key > node->right->key)
      return leftRotate(node);
       //Τέταρτη περίπτωση:Δεξιά-Αριστερή
    else if (key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  
  return node;//Επιστροφή του κόμβου αν είναι ισορροπημένος
}

//Επιστροφή του κόμβου με το μικρότερο key
AVLTree::Node *AVLTree::nodeWithMinimumValue(Node *node) {
  Node *current = node;
  while (current->left != nullptr)
    current = current->left;
  return current;
}

//Εισαγωγή στοιχείου στο δένδρο
void AVLTree::insert(int key) { root = insertNode(root, key); }

//Εύρεση ελάχιστου στοιχείου
int AVLTree::findMin() {
  if (root == nullptr) {
    return -1;
  }
  Node *current = root;
  while (current->left != nullptr)
    current = current->left;
  return current->key;
}

//Επιστροφή του μεγέθους του δένδρου
int AVLTree::size() { return getSize(root); }

//Επιστροφή πλήθους των κόμβων του δένδρου
int AVLTree::getSize(Node *root) {
  if (root == nullptr)
    return 0;
  return 1 + getSize(root->left) + getSize(root->right);
}

//Επιστροφή True/False αν έχει βρεθεί το στοιχείο
bool AVLTree::search(int key) { return searchNode(root, key); }

//Αναζήτηση ενός κόμβου και επιστροφή True/False
bool AVLTree::searchNode(Node *node, int key) {
  if (node == nullptr)
    return false;
  if (key == node->key)
    return true;
  if (key < node->key)
    return searchNode(node->left, key);
  else
    return searchNode(node->right, key);
}

//Διαγραφή ενός κόμβου και επιστροφή του κόμβου
void AVLTree::deleteTree(Node *node) {
  if (node != nullptr) {
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }
}

//Διαγραφή ενός κόμβου
AVLTree::Node *AVLTree::deleteNode(Node *root, int key) {
  //Έλεγχος αν το δένδρο είναι κενό
  if (root == nullptr)
    return root;

  //Βρίσκει αναδρομικά το κόμβο που πρέπει να διαγραφεί
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    //Κόμβος με ένα ή κανένα παιδί
    if (root->left == nullptr) {
      Node *temp = root->right;
      delete root;
      return temp;
    } else if (root->right == nullptr) {
      Node *temp = root->left;
      delete root;
      return temp;
    }
    //Κόμβος με δύο παιδιά:βρίσκει το μικρότερο κόμβο στο δεξί υποδένδρο
    Node *temp = nodeWithMinimumValue(root->right);

    root->key = temp->key;
    root->right = deleteNode(root->right, temp->key);
  }

  //Ενημέρωση ύψους του κόμβου
  root->height = 1 + max(height(root->left), height(root->right));

 //Υπολογισμός συντελεστή ισορροπίας 
  int balance = getBalanceFactor(root);

  //Αν ο κόμβος δεν είναι ισορροπημένος τοτε:
  //Πρώτη περίπτωση:Αριστερή-Αριστερή
  if (balance > 1 && getBalanceFactor(root->left) >= 0)
    return rightRotate(root);
  //Δεύτερη περίπτωση:Δεξιά-Δεξιά
  if (balance < -1 && getBalanceFactor(root->right) <= 0)
    return leftRotate(root);
  //Τρίτη περίπτωση:Αριστερή-Δεξιά
  if (balance > 1 && getBalanceFactor(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  //Τέταρτη περίπτωση:Δεξιά-Αριστερή
  if (balance < -1 && getBalanceFactor(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;//Επιστροφή του κόμβου αν είναι ισορροπημένος
}

//Επιστροφή του διαγραμμένου κόμβου
void AVLTree::remove(int key) { root = deleteNode(root, key); }
