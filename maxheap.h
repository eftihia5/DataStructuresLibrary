#ifndef MAXHEAP_H
#define MAXHEAP_H

class MaxHeap {
private:
    int* heap;     // Δείκτης στον πίνακα που αποθηκεύει τα στοιχεία του σωρού μεγίστου
    int capacity;  // Χωρητικότητα του σωρού
    int size;      // Μέγεθος (αριθμός στοιχείων) του σωρού

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();

public:
    MaxHeap(int initialCapacity = 100);

    void insert(int value);
    int getMax() const;
    int extractMax();
    bool isEmpty() const;
    int getSize() const;
};

#endif