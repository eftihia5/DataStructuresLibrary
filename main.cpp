#include "maxheap.h"
#include "minheap.h"
#include "hashtable.h"
#include "graph.h"
#include "avltree.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

void executeCommands(const string &inputFile, const string &outputFile) {

  ifstream inFile(inputFile);  //Άνοιγμα αρχείου για διάβασμα	
  ofstream outFile(outputFile);  //Άνοιγμα αρχείου για εγγραφή

  //Διαχείρηση λάθους αν δεν ανοίγει το αρχείο
  if (!inFile.is_open()) {
    cout << "Error: Unable to open input file!" << endl;
    return;
  }
  if (!outFile.is_open()) {
    cout << "Error: Unable to open output file!" << endl;
    inFile.close();
    return;
  }

  // Δημιουργία αντικειμένων για κάθε δομή
  MinHeap minHeap;
  MaxHeap maxHeap;
  HashTable hashTable(100);
  Graph graph;
  AVLTree avlTree;
  
  auto start = high_resolution_clock::now();  //Χρόνος εκκίνησης
  
  string line;
  while (getline(inFile, line)) {
    istringstream iss(line);  //Ανάγνωση γραμμής από το αρχείο
    string command;
    iss >> command;  //Διαβάζει την εντολή από το αρχείο

    //Εκτελεί τις αντίστοιχες εντολές, ανάλογα με το command
    //Σε κάθε περίπτωση διαβάζει από το αρχείο την αντίστοιχη δομή
    if (command == "BUILD") {
      string structure, filename;
      iss >> structure >> filename;
      ifstream dataFile(filename);
      if (structure == "MINHEAP") {
        int value;
        while (dataFile >> value) {
          minHeap.insert(value);
        }
        outFile << "MinHeap built successfully." << endl;
      } 
      else if (structure == "MAXHEAP") {
        int value;
        while (dataFile >> value) {
          maxHeap.insert(value);
        }
        outFile << "MaxHeap built successfully." << endl;
      }
      else if (structure == "HASHTABLE"){
        int value;
        while (dataFile >> value) {
          hashTable.insert(value);
        }
        outFile << "HashTable built successfully." << endl;
      }
      else if (structure == "GRAPH"){
        int number1, number2,weight;
        while (dataFile >> number1 >> number2 >> weight){
          graph.insert(number1, number2,weight);
        }
        outFile << "Graph built successfully." << endl;
      }
      else if (structure == "AVLTREE"){
        int value;
        while (dataFile >> value){
          avlTree.insert(value); 
        }
        outFile << "AVLTree built successfully." << endl;
      }
      else {
        cout << "Invalid structure type!" << endl;
      }
    } 
    else if (command == "GETSIZE") {
      string structure;
      iss >> structure;
      if (structure == "MINHEAP") {
        outFile << "Minheap Size: "<<minHeap.getSize() << endl;
      } else if (structure == "MAXHEAP") {
        outFile << "Maxheap Size: "<<  maxHeap.getSize() << endl;
      }
      else if (structure == "HASHTABLE"){
        outFile <<"Hashtable Size: "<< hashTable.getSize() << endl;
      }
      else if (structure == "GRAPH"){
        outFile << "Graph Size: " << graph.getSize() << endl;
      }
      else if (structure == "AVLTREE"){
        outFile << "AVLTree Size: " << avlTree.size() << endl;
      }
      else{
        outFile << "Invalid structure" << endl;
      }
    } 
    else if (command == "FINDMIN") {
      string structure;
      iss >> structure;
      if (structure == "MINHEAP") {
        if (minHeap.isEmpty())
          outFile << "EMPTY" << endl;
        else
          outFile << "Min: "<< minHeap.getMin() << endl;
      } else if (structure == "AVLTREE") {
        if (avlTree.size()==0)
          outFile << "EMPTY" << endl;
        else
          outFile << "Min: " << avlTree.findMin() << endl;
      }
      else{
        outFile << "Invalid structure" << endl;
      }
    }
    else if (command == "FINDMAX"){
      string structure;
      iss >> structure;
      if (structure == "MAXHEAP"){
        if (maxHeap.isEmpty())
          outFile << "EMPTY" << endl;
        else
          outFile << "Max: "<< maxHeap.getMax() << endl;
      }
      else{
        outFile << "Invalid structure" << endl;
      }
    }
    else if (command == "SEARCH"){
      string structure;
      iss >> structure;
      if (structure == "HASHTABLE"){
        int number;
        iss >> number;
        if (hashTable.search(number))
          outFile << "SUCCESS" << endl;
        else
          outFile << "FAILURE" << endl;
      }
      else if (structure == "AVLTREE"){
        int number;
        iss >> number;
        if (avlTree.search(number))
          outFile << "SUCCESS" << endl;
        else
          outFile << "FAILURE" << endl;
      }
      else{
        outFile << "Invalid structure" << endl;
      }
    }
    else if (command == "INSERT"){
      string structure;
      int number,number1,number2;
      iss >> structure;
      if (structure == "MINHEAP"){
        iss >> number;
        minHeap.insert(number);
        outFile << "Successfully inserted " << number << " into the heap." << endl;
      }
      else if (structure == "MAXHEAP"){
        iss >> number;
        maxHeap.insert(number);
        outFile << "Successfully inserted " << number << " into the heap." << endl;
      }
      else if (structure == "HASHTABLE"){
        iss >> number;
        hashTable.insert(number);
        outFile << "Successfully inserted " << number << " into the table." << endl;
      }
      else if (structure == "GRAPH"){
        int weight;
        iss >> number1 >> number2 >> weight;
        graph.insert(number1,number2,weight);
        outFile << "Successfully inserted of " << number1 << "-" << number2 << " edge with weight "<< weight << " into the graph." << endl;
      }
      else if (structure == "AVLTREE"){
        iss >> number;
        avlTree.insert(number);
        outFile << "Successfully inserted " << number << " into the AVL tree." << endl;
      }
      else{
        outFile << "Invalid structure" << endl;
      }
    }
    else if (command == "DELETEMIN"){
      string structure;
      iss >> structure;
      if (structure == "MINHEAP"){
        if (minHeap.isEmpty())
          outFile << "EMPTY" << endl;
        else
          outFile << "Delete Min: "<< minHeap.extractMin() << endl;
      }
    }
    else if (command == "DELETEMAX"){
      string structure;
      iss >> structure;
      if (structure == "MAXHEAP"){
        if (maxHeap.isEmpty())
          outFile << "EMPTY" << endl;
        else
          outFile << "Delete Max: "<< maxHeap.extractMax() << endl;
      }
      else{
        outFile << "Invalid structure" << endl;
      }
    }
    else if (command == "DELETE"){
      string structure;
      int number,number1,number2;
      iss >> structure;
      if (structure == "GRAPH"){
        iss >> number1 >> number2;
        graph.deleteEdge(number1,number2);
        outFile << "Successfully deleted of " << number1 << "-" << number2 << " edge." << endl;
      }
      else if (structure == "AVLTREE"){
        iss >> number;
        avlTree.remove(number);
        outFile << "Successfully deleted " << number << " from the AVL tree." << endl;
      }
      else{
        outFile << "Invalid structure" << endl;
      }
    }
    else if (command == "COMPUTESHORTESTPATH"){
      string structure;
      int number1,number2;
      iss >> structure;
      if (structure == "GRAPH"){
        iss >> number1 >> number2;
        outFile << "Shortest Path: " << graph.computeShortestPath(number1,number2) << endl;
      }
      else{
        outFile << "Invalid structure" << endl;
      }
    }
    else if (command == "COMPUTESPANNINGTREE"){
      string structure;
      iss >> structure;
      if (structure == "GRAPH"){
        outFile << "Spanning Tree: " << graph.computeSpanningTree() << endl;
      }
      else{
        outFile << "Invalid structure" << endl;
      }
    }
    else if (command == "FINDCONNECTEDCOMPONENTS"){
      string structure;
      iss >> structure;
      if (structure == "GRAPH"){
        outFile <<"Components: "<< graph.findConnectedComponents()<<endl;
      }
      else{
        outFile << "Invalid structure" << endl;
      }
    }
    else{
      outFile << "Invalid command" << endl;
    }  //Περίπτωση λάθους εντολής
  
    auto stop = high_resolution_clock::now();  //Χρόνος τερματισμού
    auto duration = duration_cast<microseconds>(stop - start); //Διάρκεια εκτέλεσης της εντολής
    outFile << "Time taken: " <<  duration.count() << " microseconds" << endl;
    start = high_resolution_clock::now();  //Επανεκκίνηση χρόνου
  }
}

int main() {                                     //Συνάρτηση για το εκτέλεση των εντολών του
  executeCommands("commands.txt", "output.txt"); //αρχείου commands.txt και επιστροφή των 
  return 0;                                      //αποτελεσμάτων στο αρχείο output.txt
}