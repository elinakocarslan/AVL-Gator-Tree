
#include "AVL.h"
#include <stack>
#include <queue>

//node height
void AVLTree::nodeHeight(Node* node) {
    if (!node->left && !node->right) { // if no childs then height is one
        node->height = 1;
    }else if (!node->left) { // if no left child then the height of the right child(ren) plus 1 is the height
        node->height = 1 + node->right->height;
    }else if (!node->right) { // if no right child then the height of the left child(ren) plus 1 is the height
        node->height = 1 + node->left->height;
    }else { // if there is two childs, get the max of both heights of both children and add 1
        node->height = 1 + std::max(node->left->height, node->right->height);
    }
}

//checking balance
int AVLTree::checkBalance(Node *node) {
    int balance = 0;
    if (!node || (!node->left) && (!node->right)) { // if node doesnt exist or is a lead node, then it is balanced
        balance = 0;
    }if (!node->left) { // if it is right concentrated then set balance to the negated height of the right subtree so that we can balance it later in insert code
        balance = node->right->height * (-1);
    }else if (!node->right) { // if it is left concentrated then set balance to the height of the left subtree so that we can balance it later in insert code
        balance = node->left->height;
    }else { // if node has both children then to check balance we have to find the difference btw both subtrees
        balance = (node->left->height - node->right->height);
    }
    return balance;
}

//rotations
Node* AVLTree::leftRotate(Node* node) { // taken from lecture, in module 4 by aman kapoor
    Node* newParent = node->right; // create newRoot as current nodes right
    Node* grandChild = node->right->left; // if the newRoot had a left child, make sure that is transferred properly

    newParent->left = node; // officially the root
    node->right = grandChild; // transferring the child to be the right of the new right child node

    nodeHeight(newParent);
    nodeHeight(node);

    return newParent;
}
Node* AVLTree::rightRotate(Node* node) {
    Node* newParent = node->left; // create newRoot as current nodes left
    Node* grandChild = node->left->right; // if the newRoot had a right child, make sure that is transferred properly

    newParent->right = node; // officially the root
    node->left = grandChild; // transferring the child to be the left of the new left child node

    nodeHeight(newParent);
    nodeHeight(node);

    return newParent;
}

//insert
void AVLTree::insert(std::string name, std::string ufid) {
    root = insertHelper(root, name, ufid);
}
Node* AVLTree::insertHelper(Node *node, std::string name, std::string ufid) {
    if (!node) {
        std::cout << "successful" << std::endl;
        return new Node(name, ufid);
    }

    if (stoi(ufid) < stoi(node->ufid)) { // if less insert to the left
        node->left = insertHelper(node->left, name, ufid);
    }else if (stoi(ufid) > stoi(node->ufid)) { // if greater insert to right
        node->right = insertHelper(node->right, name, ufid);
    }else {
        std::cout << "unsuccessful" << std::endl;
        return node; // no doubles
    }

    nodeHeight(node); //update height

    int balanceFactor = checkBalance(node); // get balance count

    if (balanceFactor > 1 && stoi(ufid) < stoi(node->left->ufid)) { // left left case
        return rightRotate(node);
    }

    if (balanceFactor < -1 && stoi(ufid) < stoi(node->right->ufid)) {  // right right case
        return leftRotate(node);
    }

    if (balanceFactor > 1 && stoi(ufid) < stoi(node->left->ufid)) {   // left right case
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balanceFactor < -1 && stoi(ufid) < stoi(node->right->ufid)) { // right left case
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

//searching
void AVLTree::searchID(std::string ufid) {
    searchIDHelper(root, ufid);
}
void AVLTree::searchIDHelper(Node* node, std::string ufid) {
    if (!node) { // doesnt exist
        std::cout << "unsuccessful" << std:: endl;
        return;
    }

    if (node->ufid == ufid) {
        std::cout << node->name << std::endl;
        return;
    }else if (stoi(ufid) < stoi(node->ufid)) { // if less than node, then check left subtree to find
        searchIDHelper(node->left, ufid);
    }else if (stoi(ufid) > stoi(node->ufid)) { // if greater than node, then check right subtree to find
        searchIDHelper(node->right, ufid);
    }
}

void AVLTree::searchNAME(std::string name) {
    searchNAMEHelper(root, name);
}
bool AVLTree::searchNAMEHelper(Node* node, std::string name) {
    if (!node) {
        std::cout << "unsuccessful" << std:: endl;
        return false;
    }

    if (node->name == name) {
        std::cout << node->ufid << std::endl;
        return true;
    }

    if (searchNAMEHelper(node->left, name)) { // first check left recursively, if found then it will be true and returned as true
        return true;
    }
    return searchNAMEHelper(node->right, name); // if not in left subtree, check right recursively
}

//printing
void AVLTree::printInOrder() {
    printInOrderHelper(root);
}
void AVLTree::printInOrderHelper(Node* node) {
    std::stack<Node*> nodes;
    Node* current = node;

    while (current) {
        nodes.push(current);
        current = current->left;
    }

    bool printedFirst = false;

    while (!nodes.empty()) {
        current = nodes.top(); // left child
        nodes.pop(); // remove left most value, so now at parent
        if (!printedFirst) {
            std::cout << current->name; // print the current node's name
            printedFirst = true;
        }else {
            std::cout << ", " << current->name;
        }

        current = current->right; // go to that right subtree

        while (current) { // traverse left child of the right subtree and push to stack
            nodes.push(current);
            current = current->left;
        }

    }
}

void AVLTree::printPreOrder() {
    printPreOrderHelper(root);
}
void AVLTree::printPreOrderHelper(Node *node) {
    std::stack<Node*> nodes;
    Node* current = node;

    if (current) {
        nodes.push(current);
    }

    bool printedFirst = false;

    while (!nodes.empty()) {
        current = nodes.top(); // top of stack node
        nodes.pop(); // remove it from stack

        if (!printedFirst) {
            std::cout << current->name;
            printedFirst = true;
        }else {
            std::cout << ", " << current->name; // print the top node
        }

        if (current->right) { // if it has right child push to stack first
            nodes.push(current->right);
        }
        if (current->left) { // push left second bc we wanna print that out first (for it to be stack top)
            nodes.push(current->left);
        }
    }
}

void AVLTree::printPostOrder() {
    printPostOrderHelper(root);
}
void AVLTree::printPostOrderHelper(Node *node) {
    std::stack<Node*> nodes;
    Node* current = node;
    std::stack<Node*> tempStack;

    if (current) {
        nodes.push(current);
    }

    bool printedFirst = false;

    while (!nodes.empty()) {
        current = nodes.top();
        nodes.pop();

        tempStack.push(current); // adds to temp stack in post order

        if (current->left) { // push left first
            nodes.push(current->left);
        }
        if (current->right) { // right second
            nodes.push(current->right);
        }
    }

    while(!tempStack.empty()) {
        current = tempStack.top(); // printing in order bc temp stack is in post order
        tempStack.pop();
        if (!printedFirst) { // makes sure no comma is printed in front of first item
            std::cout << current->name;
            printedFirst = true;
        }else {
            std::cout << ", " << current->name;
        }
    }
}

void AVLTree::printLevelCount() {
    printLevelCountHelper(root);
}
void AVLTree::printLevelCountHelper(Node* node) {
    if (node == nullptr)
        std::cout << 0 << std::endl;
    else
        std::cout << root->height << std::endl;
}


//removals
void AVLTree::remove(std::string ufid) {
    removeHelper(root, ufid);
}
Node* AVLTree::removeHelper(Node* node, std::string ufid) {
    if (!node) { // doesnt exist
        return node;
    }

    if (node->ufid == ufid) {
        std::cout << "successful" << std::endl;
        if (!node->left && !node->right) { // if node is leaf, just delete
            delete node;
            return nullptr;
        }else if (!node->left) { // if node has right child only
            Node* temp = node->right; // store right child
            delete node;
            return temp;
        }else if (!node->right) { // if node has left child only
            Node* temp = node->left; // store left child
            delete node;
            return temp;
        }else { // has two children
            Node* successor = node->right; // the bigger num is right, so it will be replaced by that
            while (successor->left){
                successor = successor->left; // if it has less values they will be successor
            }
            node->right = removeHelper(node->right, successor->ufid); // keep checking unless it has more children
        }
    }else if (stoi(ufid) < stoi(node->ufid)) { // if less than node, then check left subtree to find
        node->left = removeHelper(node->left, ufid); // the returned temp will be nodes->left so automatically replaced
    }else if (stoi(ufid) > stoi(node->ufid)) { // if greater than node, then check right subtree to find
        node->right = removeHelper(node->right, ufid); // the returned temp will be nodes->right so automatically replaced
    }else{
        std::cout << "unsuccessful" << std:: endl;
    }

    nodeHeight(node); // update height

    return node;
}

void AVLTree::removeInOrder(int index){
    removeInOrderHelper(root, index);
}
Node* AVLTree::removeInOrderHelper(Node* node, int index){
    if (!node){
        if (index > 0) {
            std::cout << "unsuccessful" << std::endl; // if index doesn't exist cant be removed
        }
        return node;
    }

    node->left = removeInOrderHelper(node->left, index);
    if (index == 0) {
        std::cout << "successful" << std::endl;
        if (!node->left && !node->right) { // if node is leaf, just delete
            delete node;
            return nullptr;
        }else if (!node->left) { // if node has right child only
            Node* temp = node->right; // store right child
            delete node;
            return temp;
        }else if (!node->right) { // if node has left child only
            Node* temp = node->left; // store left child
            delete node;
            return temp;
        }else { // has two children
            Node* successor = node->right; // the bigger num is right, so it will be replaced by that
            while (successor->left){
                successor = successor->left; // if it has fewer values they will be successor
            }
            node->right = removeInOrderHelper(node->right, --index); // remove successor
        }
    }else{
        index--;
        node->right = removeInOrderHelper(node->right, index); // check right subtree
    }

    nodeHeight(node); // update height

    return node;
}


