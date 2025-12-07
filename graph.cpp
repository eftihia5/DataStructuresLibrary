#include "graph.h"
#include <iostream>
using namespace std;

//Κατασκευαστής για την κλάση Graph
Graph::Graph() {
  for (int i = 0; i < MAX_VERTICES; ++i) {
    adjList[i].initialized = false; //Αρχικοποιεί τον πίνακα με false
    adjList[i].size = 0; //Αρχικοποιεί το μέγεθος της λίστας γειτνίασης με 0
    adjList[i].capacity =
        5; //Αρχικοποιεί την αρχική χωρητικότητα της λίστας γειτνίασης με 5
    adjList[i].vertices = new int[5]; //Αποθήκευση των γειτόνων της κάθε κορυφής
    adjList[i].weights = new int[5]; //Αποθήκευση των βαρών της ακμής
  }
}

//Εισαγωγή ακμής στο γράφο
void Graph::insert(int v1, int v2, int weight) {
  if (v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 || v2 >= MAX_VERTICES)
    return; //Έλεγχος εγκυρότητας

  //Αρχικοποίηση των κορυφών v1 και v2
  if (!adjList[v1].initialized) {
    adjList[v1].initialized = true;
  }
  if (!adjList[v2].initialized) {
    adjList[v2].initialized = true;
  }

  if (adjList[v1].size == adjList[v1].capacity) {
    // Προσαρμογή του μεγέθους της λίστας γειτνίασης για την κορυφή v1
    int newCapacity = adjList[v1].capacity * 2;
    int *newVertices = new int[newCapacity];
    int *newWeights = new int[newCapacity];
    for (int j = 0; j < adjList[v1].size; ++j) {
      newVertices[j] = adjList[v1].vertices[j];
      newWeights[j] = adjList[v1].weights[j];
    }
    delete[] adjList[v1].vertices;
    delete[] adjList[v1].weights;
    adjList[v1].vertices = newVertices;
    adjList[v1].weights = newWeights;
    adjList[v1].capacity = newCapacity;
  }

  //Προσθήκη ακμής στη λίστα γειτνίασης της κορυφής v1
  adjList[v1].vertices[adjList[v1].size] = v2;
  adjList[v1].weights[adjList[v1].size] = weight;
  ++adjList[v1].size;

  if (adjList[v2].size == adjList[v2].capacity) {
    // Προσαρμογή του μεγέθους της λίστας γειτνίασης για την κορυφή v2
    int newCapacity = adjList[v2].capacity * 2;
    int *newVertices = new int[newCapacity];
    int *newWeights = new int[newCapacity];
    for (int j = 0; j < adjList[v2].size; ++j) {
      newVertices[j] = adjList[v2].vertices[j];
      newWeights[j] = adjList[v2].weights[j];
    }
    delete[] adjList[v2].vertices;
    delete[] adjList[v2].weights;
    adjList[v2].vertices = newVertices;
    adjList[v2].weights = newWeights;
    adjList[v2].capacity = newCapacity;
  }

  //Προσθήκη ακμής στη λίστα γειτνίασης της κορυφής v2
  adjList[v2].vertices[adjList[v2].size] = v1;
  adjList[v2].weights[adjList[v2].size] = weight;
  ++adjList[v2].size;
}

//Εύρεση κόστους ελάχιστης διαδρομής από την κορυφή startVertex στην κορυφή
//endVertex με τον αλγόριθμο Dijkstra
int Graph::computeShortestPath(int startVertex, int endVertex) {
  if(getSize()==0) //Περίπτωση που είναι άδειος ο γράφος
    return 0;
  int distance[MAX_VERTICES];
  bool processed[MAX_VERTICES] = {
      false}; //Αποθήκευση αν μια κορυφή έχει επισκεφθεί
  //Αρχικοποίηση πίνακα distance
  for (int i = 0; i < MAX_VERTICES; ++i) {
    distance[i] = INF;
  }

  distance[startVertex] = 0; //Αρχικοποίηση του κόστους της πρώτης διαδρομής

  //Εύρεση κορυφής με την μικρότερη απόσταση που δεν έχει επισκεφθεί
  while (true) {
    int minDistance = INF;
    int currentVertex = -1;
    //Προσπέλαση όλων των κορυφών και εύρεση μικρότερης απόστασης
    for (int i = 0; i < MAX_VERTICES; ++i) {
      if (!processed[i] && distance[i] < minDistance) {
        minDistance = distance[i];
        currentVertex = i;
      }
    }
    //Αν δεν υπάρχει κορυφή με την μικρότερη απόσταση σταματάει ο βρόχος
    if (currentVertex == -1) {
      break;
    }

    processed[currentVertex] = true; //Αποθήκευση κορυφής ως επεξεργασμένη

    //Για κάθε γείτονα ενημερώνει την απόσταση αν βρει μια μικρότερη
    for (int i = 0; i < adjList[currentVertex].size; ++i) {
      int neighbor = adjList[currentVertex].vertices[i];
      int weight = adjList[currentVertex].weights[i];
      if (distance[currentVertex] + weight < distance[neighbor]) {
        distance[neighbor] = distance[currentVertex] + weight;
      }
    }
  }
  return distance[endVertex];
}

//Εύρεση κόστους του ελάχιστου εκτεινόμενου δένδρου
int Graph::computeSpanningTree() {
  bool inMST[MAX_VERTICES] = {false}; // Πίνακας που ελέγχει αν μια κορυφή περιλαμβάνεται στο Spanning Tree
  int key[MAX_VERTICES]; // Πίνακας που αποθηκεύει το ελάχιστο βάρος ακμής για όλες τις κορυφές
  int parent[MAX_VERTICES]; // Αποθηκεύει τον γονέα κάθε κορυφής
  int treeWeight = 0; // Αποθηκεύει το συνολικό βάρος
  int numVertices = getSize(); // Πλήθος των κορυφών

  for (int i = 0; i < MAX_VERTICES; ++i) {
    key[i] = INF;   // Αρχικοποίηση του πίνακα key
    parent[i] = -1; // Αρχικοποίση του πίνακα parent
  }

  //Εύρεση πρώτης αρχικοποιημένης μεταβλητής
  int startVertex = -1;
  for (int i = 0; i < MAX_VERTICES; ++i) {
    if (adjList[i].initialized) {
      startVertex = i;
      break;
    }
  }

  if (startVertex == -1)
    return 0; // Αν δεν υπάρχουν κορυφές, τότε επιστρέφει 0

  key[startVertex] = 0;
  //Εύρεση Spanning Tree
  for (int count = 0; count < numVertices - 1; ++count) {
    int u = -1, minKey = INF;

    // Εύρεση κορυφής με την ελάχιστη τιμή key που δεν περιλαμβάνεται στο Spanning Tree
    for (int v = 0; v < MAX_VERTICES; ++v) {
      if (adjList[v].initialized && !inMST[v] && key[v] < minKey) {
        minKey = key[v];
        u = v;
      }
    }

    if (u == -1)
      break; // Αν υπάρχει απομονωμένει κορυφή τερματίζει τον βρόχο

    inMST[u] = true; //Προσθήκη κορυφής στο Spanning Tree

    for (int i = 0; i < adjList[u].size; ++i) {
      int v = adjList[u].vertices[i];
      int weight = adjList[u].weights[i];
      //Ελέγχει αν ο γείτονας 'v' δεν περιλαμβάνεται στο Spanning Tree
      //Ελέγχει αν το βάρος του γείτονας είναι μικρότερο από το ελάχιστο βάρος που έχει ήδη επιστραφεί
      if (!inMST[v] && weight < key[v]) {
        key[v] = weight; // Ενημερώνει την τιμή key με το νέο ελάχιστο βάρος
        parent[v] = u; // Ενημερώνει τον γονέα με την τρέχουσα κορυφή
      }
    }
  }

  for (int i = 0; i < MAX_VERTICES; ++i) {
    //Ελέγχει αν η κορυφή 'i' είναι αρχικοποιημένη και έχει γονέα
    if (adjList[i].initialized && parent[i] != -1) {
      for (int j = 0; j < adjList[i].size; ++j) {
        if (adjList[i].vertices[j] == parent[i]) {
          treeWeight += adjList[i].weights[j]; //Προσθέτει το βάρος του γείτονα
          break;
        }
      }
    }
  }

  return treeWeight;
}

//Διαγραφή ακμής από τον γράφο
void Graph::deleteEdge(int v1, int v2) {
  if (v1 < 0 || v1 >= MAX_VERTICES || v2 < 0 ||
      v2 >= MAX_VERTICES) //Έλεγχος εγκυρότητας
    return;
  //Προσπέλαση των γειτόνων της κορυφης v1
  for (int i = 0; i < adjList[v1].size; ++i) {
    //Εύρεση γειτόνου v2
    if (adjList[v1].vertices[i] == v2) {
      //Μετακίνηση όλων των στοιχείων μετά τον v2
      for (int j = i; j < adjList[v1].size - 1; ++j) {
        adjList[v1].vertices[j] = adjList[v1].vertices[j + 1];
        adjList[v1].weights[j] = adjList[v1].weights[j + 1];
      }
      --adjList[v1].size; //Μειώνει το μέγεθος της λίστας
      break;
    }
  }

  //Προσπέλαση των γειτόνων της κορυφης v2
  for (int i = 0; i < adjList[v2].size; ++i) {
    //Εύρεση γειτόνου v1
    if (adjList[v2].vertices[i] == v1) {
      //Μετακίνηση όλων των στοιχείων μετά τον v1
      for (int j = i; j < adjList[v2].size - 1; ++j) {
        adjList[v2].vertices[j] = adjList[v2].vertices[j + 1];
        adjList[v2].weights[j] = adjList[v2].weights[j + 1];
      }
      --adjList[v2].size; //Μειώνει το μέγεθος της λίστας
      break;
    }
  }
}

//Αναζήτηση κατά πλάτος (BFS) στον γράφο
void Graph::BFS(int startVertex, bool *visited) {
  int queue[MAX_VERTICES];
  int front = 0, rear = -1;
  visited[startVertex] = true; //Ενημερώνει ότι η πρώτη κορυφή έχει επισκεφθεί
  queue[++rear] = startVertex; //Προσθέτει την αρχική κορυφή στο queue
  //Εκτελείται όσο υπάρχουν κορυφές στο queue
  while (front <= rear) {
    int currentVertex = queue[front++];
    //Διατρέχει τους γείτονες της κορυφής
    for (int i = 0; i < adjList[currentVertex].size; ++i) {
      if (!visited[adjList[currentVertex].vertices[i]]) {
        visited[adjList[currentVertex].vertices[i]] =
            true; //Ενημερώνει ότι η κορυφή έχει επισκεφθεί
        queue[++rear] = adjList[currentVertex].vertices[i]; //Προσθέτει την κορυφή στο queue
      }
    }
  }
}

//Εύρεση πλήθους των συνεκτικών συνιστωσών του γράφου
int Graph::findConnectedComponents() {
  int count = 0 ;
  bool visited[MAX_VERTICES] = {false}; //Αρχικοποίηση του πίνακα visited
  //Διατρέχει όλες τις κορυφές
  for (int i = 0; i < MAX_VERTICES; ++i) {
    if (!visited[i] && adjList[i].initialized) {
      count++;
      BFS(i, visited); //Καλεί την BFS για κάθε μη επισκέψιμη κορυφή
    }
  }
  return count;
}

//Υπολογισμός του μεγέθους του γράφου
int Graph::getSize() {
  int numVertices = 0;
  //Διατρέχει όλες τις κορυφές
  for (int i = 0; i < MAX_VERTICES; ++i) {
    //Ελέγχει αν η κορυφή 'i' είναι αρχικοποιημένη
    if (adjList[i].initialized) {
      ++numVertices; //Αυξάνει τον αριθμό των κορυφών
    }
  }
  return numVertices;
}
