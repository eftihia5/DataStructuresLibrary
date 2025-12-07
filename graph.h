#ifndef GRAPH_H
#define GRAPH_H

const int MAX_VERTICES = 1000;
const int INF = 1000000000; 

struct AdjacencyList {
    bool initialized;//Δείχνει αν η κορυφή έχει αρχικοποιηθεί
    int size;//Μέγεθος της λίστας γειτνίασης 
    int capacity;//Χωριτηκότητα της λίστας γειτνίασης
    int* vertices;//Δείκτης σε πίνακα γειτόνων
    int* weights;//Δείκτης σε πίνακα βαρών
};

class Graph {

private:
AdjacencyList adjList[MAX_VERTICES];//Περιέχει τις λίστες γειτνίασης για κάθε κορυφή

public:
    Graph();
    void insert(int v1, int v2, int weight);//Προσθήκη ακμής μεταξύ των δύο κορυφών
    void BFS(int startVertex, bool* visited);//Αναζήτηση με διάσχιση BFS
    void deleteEdge(int v1, int v2);//Διαγραφή ακμής μεταξύ των δύο κορυφών
    int computeShortestPath(int startVertex, int endVertex);//Υπολογισμός μικρότερης διαδρομής μεταξύ των δύο κορυφών
    int computeSpanningTree();//Υπολογισμός συνολικού βάρους του MST
    int findConnectedComponents();//Υπολογισμός αριθμού συνδεδεμένων συνιστωσών
    int getSize();//Επιστροφή μεγέθους του Graph


};


#endif