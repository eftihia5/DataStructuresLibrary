#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
using namespace std;

// Κλάση που αναπαριστά έναν κόμβο της συνδεδεμένης λίστας
class Node {
public:
  int data;
  Node *next;

  Node(int value) : data(value), next(nullptr) {}
};

// Κλάση που αναπαριστά μία συνδεδεμένη λίστα
class LinkedList {
private:
  Node *head; // Δείκτης στον πρώτο κόμβου

public:
  LinkedList() : head(nullptr) {}

  // Καταστροφέας
  ~LinkedList() {
    Node *current = head;
    while (current != nullptr) {
      Node *nextNode = current->next;
      delete current;
      current = nextNode;
    }
  }

  // Εισαγωγή νέου κόμβου
  void insert(int value) {
    Node *newNode = new Node(value);
    newNode->next = head;
    head = newNode;
  }

  // Έυρεση κόμβου με την τιμή value
  bool search(int value) {
    Node *current = head;
    while (current != nullptr) {
      if (current->data == value) {
        return true;
      }
      current = current->next;
    }
    return false;
  }

  // Μέγεθος λίστας
  int size() {
    int count = 0;
    Node *current = head;
    while (current != nullptr) {
      count++;
      current = current->next;
    }
    return count;
  }
};

class HashTable {
private:
  int size; // Μέγεθος του πίνακα κατακερματισμού
  LinkedList *table; // Πίνακας κατακερματισμού
  int hash(int key); // Συνάρτηση κατακερματισμού

public:
  HashTable(int size);  // Κατασκευαστής
  void insert(int key); // Εισαγωγή στοιχείου στον πίνακα κατακερματισμού
  bool search(int key); // Αναζήτηση στοιχείου στον πίνακα κατακερματισμού
  int getSize(); // Επιστροφή του μεγέθους του πίνακα κατακερματισμού
};

#endif
