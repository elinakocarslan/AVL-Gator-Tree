#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H

#endif //PROJECT1_AVL_H
#include <iostream>

struct Node {
    //node atributes
    std::string name;
    std::string ufid;
    int height;
    Node* left;
    Node* right;

    Node (std::string _name, std::string _ufid){
        name = _name;
        ufid = _ufid;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
    Node(){};
    ~Node(){};
};

class AVLTree {
private:
    Node* root = nullptr;
    Node* insertHelper(Node* node, std::string name, std::string ufid);
    void searchIDHelper(Node* node, std::string ufid);
    void searchNAMEHelper(Node* node, std::string name);
    Node* leftRotate(Node* x);
    Node* rightRotate(Node* y);
    void nodeHeight(Node* node);
    int checkBalance(Node* node);
    void printInOrderHelper(Node* node);
    void printPreOrderHelper(Node* node);
    void printPostOrderHelper(Node* node);
    void printLevelCountHelper(Node* node);
    Node* removeHelper(Node* node, std::string ufid);
    Node* removeInOrderHelper(Node* node, int& index);



public:
    AVLTree() : root(nullptr){};
    void insert(std::string name, std::string ufid); //level order traversal
    void searchID(std::string ufid);
    void searchNAME(std::string name);
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
    void printLevelCount();
    void remove(std::string ufid);
    void removeInOrder(int index);

    ~AVLTree() {delete root;}; // use post order traversal to delete nodes

};

