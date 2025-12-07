#ifndef AVLTREE_H
#define AVLTREE_H

class AVLTree {
private:
    //Αναπαράσταση κόμβου του δένδρου
    struct Node {
        int key;
        Node* left;//Δείκτης στο αριστερό παιδί
        Node* right;//Δείκτης στο δεξί παιδί
        int height;//Ύψος του κόμβου
    };

    Node* root;//Δείκτης στην ρίζα του δένδρου

    Node* newNode(int key);//Δημιουργία νέου κόμβου
    Node* rightRotate(Node* y);//Απλή δεξιά περιστροφή
    Node* leftRotate(Node* x);//Απλή αριστερή περιστροφή
    int height(Node* N);//Ύψος κόμβου
    int max(int a, int b);//Επιστροφή του μεγαλύτερου
    int getBalanceFactor(Node* N);//Επιστροφή συντελεστή ισορροπίας 
    Node* insertNode(Node* node, int key);//Εισαγωγή νέας κορυφή
    Node* nodeWithMinimumValue(Node* node);//Επιστροφή ελάχιστης κορυφής
    int getSize(Node* root);//Επιστροφή του μεγέθους του υποδένδρου με ρίζα root
    bool searchNode(Node* node, int key);//Αναζήτηση κόμβου στο υποδένδρου με ρίζα node
    Node* deleteNode(Node* root, int key);//Διαγραφή κόμβου από το υποδένδρο με ρίζα root
    void deleteTree(Node* node);//Διαγραφή όλου του υποδένδρου

public:
AVLTree();//Κατασκευαστής της κλάσης 

void insert(int key);//Εισαγωγή νέας κορυφής στο δένδρο
void remove(int key);//Αφαίρεση κορυφής από το δένδρο
int findMin();//Επιστροφή της ελάχιστης κορυφής στο δένδρο
int size();//Επιστροφή του μεγέθους του δένδρου
bool search(int key);//Αναζήτηση κορυφής στο δένδρο 
};

#endif