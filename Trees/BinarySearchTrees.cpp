#include "BinarySearchTrees.h"
#include <iostream>
#include <queue>

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

BinarySearchTree::Node::Node(DataType newval) {
    val = newval;    // Value of the node.
    left = nullptr;      // Pointer to the left node.
    right = nullptr;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    if (n == NULL) return -1;
    return std::max(getNodeDepth(n->left), getNodeDepth(n->right)) + 1;
}

void BinarySearchTree::AVLUpdate(Node* n) {
    if (n != NULL){
        n->avlBalance = getNodeDepth(n);
    }
}

BinarySearchTree::BinarySearchTree() {
    root_ = nullptr;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree() {
    if (size_ > 0 ){
        remove(max());
    }
    if (size_> 0 ){
        remove(min());
    }
}

unsigned int BinarySearchTree::size() const {
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const {
    Node* current = root_;
    while (current->right != nullptr){
        current = current->right;
    }
    return current->val;

}

BinarySearchTree::DataType BinarySearchTree::min() const {
    Node* current = root_;
    Node* temp = current;
    while (current->left != nullptr){
        temp = current->left;
        current = temp;
    }
    return current->val;
}

unsigned int BinarySearchTree::depth() const {
    return getNodeDepth(root_);
}

void BinarySearchTree::print() const {

}

bool BinarySearchTree::exists(DataType val) const {
    Node* current = root_;
    while (current != nullptr){
        if (current == nullptr){ return false;}
        else if (current->val == val){
            return true;
        }
        else {
            if (val > current->val){
                current = current->right;
            }
            else{
                current = current->left;
            }
        }
    }
}

BinarySearchTree::Node* BinarySearchTree::getRootNode() {
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress() {
    return (&root_);
}

bool BinarySearchTree::insert(DataType val) {
    Node* current = root_;
    Node* parent = root_;
    if (root_ == nullptr){
        root_ = new Node(val);
        size_++;
        return true;
    }
    while (current != nullptr){
        if (val == current->val){
            return false;
        }
        else if (val > current->val){
            parent = current;
            current = parent->right;

        }
        else{
            parent = current;
            current = parent->left;
        }
    }

    Node* insertnew = new Node(val);
    if (val > parent->val){
        parent->right = insertnew;
    }
    else{
        parent->left = insertnew;
    }
    size_++;
    return true;
}

bool BinarySearchTree::remove(DataType val) {
    Node* current = root_;
    Node* parent = root_;
    bool isLeft = false;
    if (root_ == nullptr){
        root_ = new Node(val);
    }
    while ( current != nullptr && current->val != val ) {

        if (val > current->val){
            parent = current;
            current = parent->right;
        }
        else{
            parent = current;
            current = parent->left;
            isLeft = true;
        }
    }
    if (current == nullptr){
        return false;
    }

    Node* sus = current->right; //successor
    Node* parent_sus = current;

    //case 1) remove leaf node
    if (current->left == nullptr && current->right == nullptr){
        //case 1.1) leaf is root
        if (current == root_) {
            root_ = nullptr;
            size_ = 0;
            delete current;

            return true;
        }
        current = nullptr;
        delete current;
        if (isLeft) {
            parent->left = nullptr;

        }
        else{
            parent->right = nullptr;
        }
        parent = nullptr;
        delete parent;

        size_--;
        return true;
    }

        //case 2) Only right child

    else if (current->left == nullptr && current-> right!= nullptr){
        if(isLeft){
            parent->left = current->right;
        }
        else{
            parent->right = current->right;
        }
        current = nullptr;
        delete current;
        parent = nullptr;
        delete parent;
        size_--;
        return true;
    }

        //case 3) Only Left child
    else if (current->left != nullptr && current->right == nullptr){
        if(isLeft){
            parent->left = current->left;
        }
        else{
            parent->right = current->left;
        }
        current = nullptr;
        delete current;
        parent = nullptr;
        delete parent;
        size_--;
        return true;
    }

        //case 4) left and right children

    else {
        parent_sus = sus;
        while(sus->left != nullptr){
            parent_sus = sus;
            sus = parent_sus->left;
        }

        if (sus->right != nullptr){
            parent_sus->left = sus->right;
        }
        else{
            parent_sus->left =nullptr;
        }
        current->val = sus->val;
        //Missing from 3.1 submission (fixed in AVL debugging)
        if (parent_sus->right == sus){
            parent_sus->right = sus->left;
        }
        else{
            parent_sus->left = sus->left;
        }
        current->right = nullptr;
        current= nullptr;
        delete current;
        parent = nullptr;
        delete parent;
        sus = nullptr;
        delete sus;
        parent_sus = nullptr;
        delete parent_sus;
        size_--;
        return true;
    }

}

Node* BinarySearchTree::findParent(DataType val) {

    Node* currentNode = root_;
    Node* parentNode = NULL;

    if (!exists(val)) return parentNode;

    while (currentNode->val != val) {

        // Continue to search on left subtree
        if (val < currentNode->val) {
            parentNode = currentNode;
            currentNode = currentNode->left;
        }
            // Continue to search on right subtree
        else { // (val > currentNode->val)
            parentNode = currentNode;
            currentNode = currentNode->right;
        }
    }
    return parentNode;
}

Node* findPredecessor(Node* ptr) {

    // ptr can be thought of as previousNode
    Node* ptrNext = ptr->left; // i.e. currentNode

    while (ptrNext != NULL) {
        ptr = ptrNext;
        ptrNext = ptrNext->right;
    }
    return ptr;
}
