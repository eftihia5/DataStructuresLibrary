#include "minheap.h"
#include <iostream>

using namespace std;

//Κατασκευαστής για την κλάση MinHeap
MinHeap::MinHeap(int initialCapacity) : capacity(initialCapacity), size(0) {
  heap = new int[capacity]; 
}

//Εισαγωγή στοιχείου με βάση την heapifyUp
void MinHeap::insert(int value) {
  if (size == capacity) {
    resize();
  }
  heap[size] = value;
  heapifyUp(size);
  size++;
}

//Επιστροφή του μικρότερου (πρώτου) στοιχείου
int MinHeap::getMin() const { return heap[0]; }

//Εξαγωγή του μικρότερου (πρώτου) στοιχείου και αναδιάταξη του σωρού ελαχίστων με την heapifyDown
int MinHeap::extractMin() {
  int minValue = heap[0];
  heap[0] = heap[size - 1];
  size--;
  heapifyDown(0);
  return minValue;
}

//Ελέγχει αν ο σωρός είναι άδειος
bool MinHeap::isEmpty() const { return size == 0; }

//Επιστρέφει το μέγεθος του σωρού
int MinHeap::getSize() const { return size; }

//Εκτελεί την heapifyUp για το στοιχείο στην θέση index
void MinHeap::heapifyUp(int index) {
  while (index > 0 && heap[index] < heap[(index - 1) / 2]) {
    swap(heap[index], heap[(index - 1) / 2]);
    index = (index - 1) / 2;
  }
}

//Εκτελεί την heapifyDown για το στοιχείο στην θέση index
void MinHeap::heapifyDown(int index) {
  int smallest = index;
  int leftChild = 2 * index + 1;
  int rightChild = 2 * index + 2;

  if (leftChild < size && heap[leftChild] < heap[smallest]) {
    smallest = leftChild;
  }
  if (rightChild < size && heap[rightChild] < heap[smallest]) {
    smallest = rightChild;
  }
  if (smallest != index) {
    swap(heap[index], heap[smallest]);
    heapifyDown(smallest);
  }
}

//Ελέγχει αν ο σωρός είναι γεμάτος και αν ναι διπλασιάζει το μέγεθός του
void MinHeap::resize() {
  int *newHeap = new int[capacity * 2];
  for (int i = 0; i < size; i++) {
    newHeap[i] = heap[i];
  }
  delete[] heap;
  heap = newHeap;
  capacity *= 2;
}