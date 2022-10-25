
#include "AVLTrees.h"
#include <cstdlib>
#include <algorithm>

using namespace std;

int FindHeight(BinarySearchTree::Node *node)
{
    if (node == NULL){return 0;}
    else {return (std::max(FindHeight(node->left), FindHeight(node->right))+1);}
}

void RightRight(BinarySearchTree::Node **pTop, BinarySearchTree::Node *alpha){
    BinarySearchTree::Node *A = alpha->left;
    alpha->left = A->right;
    A->right= alpha;
    if (*pTop == alpha) {
        *pTop = A;
    }
    else {

        BinarySearchTree::Node *temp = *pTop;
        BinarySearchTree::Node **parentPointerToAlpha = nullptr;
        do{
            if(alpha->val > temp->val)  {
                parentPointerToAlpha = &temp->right;
                temp = temp->right;
            }
            else if (alpha->val < temp->val) {
                parentPointerToAlpha = &temp->left;
                temp = temp->left;
            }
        }
        while (temp->val != alpha->val);
        *parentPointerToAlpha = A;
    }
}



void LeftLeft(BinarySearchTree::Node **pTop, BinarySearchTree::Node *alpha){
    BinarySearchTree::Node *A = alpha->right;
    alpha->right = A->left;
    A->left = alpha;
    if (*pTop == alpha) {
        *pTop = A;
    }
    else {
        BinarySearchTree::Node *temp = *pTop;
        BinarySearchTree::Node **parentPointerToAlpha = nullptr;
        do{
            if(alpha->val > temp->val)  {
                parentPointerToAlpha = &temp->right;
                temp = temp->right;
            }
            else if (alpha->val < temp->val) {
                parentPointerToAlpha = &temp->left;
                temp = temp->left;
            }
        }
        while (temp->val != alpha->val);
        *parentPointerToAlpha = A;
    }
}


void LeftRight(BinarySearchTree::Node **pTop, BinarySearchTree::Node *alpha){
    //Do a left then right rotation with A = alpha left
    BinarySearchTree::Node *A = alpha->left;
    LeftLeft(pTop, A);
    RightRight(pTop, alpha);
}



BinarySearchTree::Node RightLeft(BinarySearchTree::Node **pTop, BinarySearchTree::Node *alpha){
    //Do a Right then left with A = alpha right
    BinarySearchTree::Node *A = alpha->right;
    RightRight(pTop, A);
    LeftLeft(pTop, alpha);
}






bool AVLTree::insert(DataType val)
{
    bool result = BinarySearchTree::insert(val);
    if (result == false ) {return false;} //return false if result fails
    BinarySearchTree::Node *root;
    root = BinarySearchTree::getRootNode();
    BinarySearchTree::Node **addressRoot;
    addressRoot = BinarySearchTree::getRootNodeAddress();


    if(root->val == val) {return true;}
    BinarySearchTree::Node *temp;
    temp = root;
    BinarySearchTree::Node *tempParent;
    BinarySearchTree::Node *alpha = nullptr;
    while (temp->val != val) {
        tempParent = temp;
        if(val>temp->val) {
            temp = temp->right;
        }
        else if (val<temp->val) {
            temp = temp->left;
        }
        //check if unbalanced
        int leftHeight = FindHeight(tempParent->left);
        int rightHeight = FindHeight(tempParent->right);
        if(abs(leftHeight - rightHeight) > 1 ) {
            alpha = tempParent;
        }
    }

    if(!alpha) return true; // Cases check
    if (val < alpha->val && val<alpha->left->val){ // single right rotation
        RightRight(addressRoot,alpha);
    }
    else if (val > alpha->val && val > alpha->right->val ){// single left rotation
        LeftLeft(addressRoot,alpha);
    }
    else if ( val < alpha->val && val > alpha->left->val ) {// left right
        LeftRight(addressRoot,alpha);
    }
    else if (val > alpha->val && val < alpha->right->val ) {//right left
        RightLeft(addressRoot, alpha);
    }
    return true;
}


bool AVLTree::remove(DataType val)
{
    bool result = BinarySearchTree::remove(val);
    int balanceFactor ;
    if (result == false) return false;
    BinarySearchTree::Node *root;
    root = BinarySearchTree::getRootNode();
    BinarySearchTree::Node **addressRoot;
    addressRoot = BinarySearchTree::getRootNodeAddress();
    // if N is at root node, nothing is unbalanced, just return
    if(root == NULL || root->val == val ) return true;
    BinarySearchTree::Node *temp;
    temp = root;
    BinarySearchTree::Node *tempParent;
    BinarySearchTree::Node *alpha = nullptr;
    while (temp != nullptr && temp->val != val){
        tempParent = temp;
        if(val>temp->val){
            temp = temp->right;
        }
        else if (val<temp->val) {
            temp = temp->left;
        }

        // now check if tempParent is unbalanced
        int leftHeight =  FindHeight(tempParent->left);
        int rightHeight = FindHeight(tempParent->right);
        if(abs(leftHeight - rightHeight) > 1) {
            alpha = tempParent;
            temp = nullptr;
        }
        balanceFactor = leftHeight - rightHeight;
    }


    if(!alpha) return true; // alpha = unbalanced
    int DifferenceL = 0;
    int DifferenceR = 0;
    if (alpha->left != nullptr){
        DifferenceL = FindHeight(alpha->left->left) - FindHeight(alpha->left->right) ;
    }

    if (alpha->right !=nullptr){
        DifferenceR = FindHeight(alpha->right->left) - FindHeight(alpha->right->right) ;
    }

    if (balanceFactor > 1) { //then need right rot
        if(DifferenceL >= 1)
            RightRight(addressRoot,alpha); // right right
        else
            LeftRight(addressRoot,alpha); // left left
    }
    else {
        if (DifferenceR <= 0)
            LeftLeft(addressRoot, alpha);
        else{
            RightLeft(addressRoot, alpha);
        }
    }
    return true;
}