#include "maxheap.h"
#include <iostream>

using namespace std;

//Κατασκευαστής για την κλάση MaxHeap
MaxHeap::MaxHeap(int initialCapacity) : capacity(initialCapacity), size(0) {
  heap = new int[capacity];
}

//Εισαγωγή στοιχείου με βάση την heapifyUp
void MaxHeap::insert(int value) {
  if (size == capacity) {
    resize();
  }
  heap[size] = value;
  heapifyUp(size);
  size++;
}

//Επιστροφή του μεγαλύτερου (πρώτου) στοιχείου
int MaxHeap::getMax() const { return heap[0]; }

//Εξαγωγή του μεγαλύτερου (πρώτου) στοιχείου και αναδιάταξη του σωρού ελαχίστων με την heapifyDown
int MaxHeap::extractMax() {
  int maxValue = heap[0];
  heap[0] = heap[size - 1];
  size--;
  heapifyDown(0);
  return maxValue;
}

//Ελέγχει αν ο σωρός είναι άδειος
bool MaxHeap::isEmpty() const { return size == 0; }

//Επιστρέφει το μέγεθος του σωρού
int MaxHeap::getSize() const { return size; }

//Εκτελεί την heapifyUp για το στοιχείο στην θέση index
void MaxHeap::heapifyUp(int index) {
  while (index > 0 && heap[index] > heap[(index - 1) / 2]) {
    swap(heap[index], heap[(index - 1) / 2]);
    index = (index - 1) / 2;
  }
}

//Εκτελεί την heapifyDown για το στοιχείο στην θέση index
void MaxHeap::heapifyDown(int index) {
  int largest = index;
  int leftChild = 2 * index + 1;
  int rightChild = 2 * index + 2;

  if (leftChild < size && heap[leftChild] > heap[largest]) {
    largest = leftChild;
  }
  if (rightChild < size && heap[rightChild] > heap[largest]) {
    largest = rightChild;
  }
  if (largest != index) {
    swap(heap[index], heap[largest]);
    heapifyDown(largest);
  }
}

//Ελέγχει αν ο σωρός είναι γεμάτος και αν ναι διπλασιάζει το μέγεθός του
void MaxHeap::resize() {
  int *newHeap = new int[capacity * 2];
  for (int i = 0; i < size; i++) {
    newHeap[i] = heap[i];
  }
  delete[] heap;
  heap = newHeap;
  capacity *= 2;
}