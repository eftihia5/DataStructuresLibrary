#ifndef MINHEAP_H
#define MINHEAP_H

class MinHeap {
private:
    int* heap;     // Δείκτης στον πίνακα που αποθηκεύει τα στοιχεία του σωρού ελαχίστων
    int capacity;  // Χωρητικότητα του σωρού
    int size;      // Μέγεθος (αριθμός στοιχείων) του σωρού

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();

public:
    MinHeap(int initialCapacity = 100);

    void insert(int value);
    int getMin() const;
    int extractMin();
    bool isEmpty() const;
    int getSize() const;
};

#endif 