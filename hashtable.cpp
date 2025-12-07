#include "hashtable.h"
#include <iostream>
using namespace std;

//Κατασκευαστής της κλάσης Hastable
HashTable::HashTable(int size) : size(size) {
    table = new LinkedList[size];    // Δημιουργία δυναμικού πίνακα με συνδεδεμένες λίστες
}

// Υπολογισμός του hash value
int HashTable::hash(int key) {
    return key % size;    
}

//Εισαγωγή στοιχείου στον πίνακα table
void HashTable::insert(int key) {
    int index = hash(key);
    table[index].insert(key);
}

//Εύρεση του key στον πίνακα table
bool HashTable::search(int key) {
    int index = hash(key);
    return table[index].search(key);
}

//Υπολογισμός μεγέθους του πίνακα table
int HashTable::getSize() {
    int count = 0;
    for (int i = 0; i < size; i++){
        count += table[i].size();
    }
    return count;
}