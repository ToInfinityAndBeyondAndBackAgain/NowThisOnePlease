//
// Created by Carly Knibutat on 2022-10-24.
//

#ifndef NOWTHISONEPLEASE_AVLTREES_H
#define NOWTHISONEPLEASE_AVLTREES_H


#include "BinarySearchTrees.h"
#include <stack>

using namespace std;

class AVLTree : public BinarySearchTree {
public:
    // Overriden insert and remove functions
    // Do not modify these definitions

    // The AVL tree should be kept balanced after calling just insert or remove.
    bool insert(DataType val);
    bool remove(DataType val);


private:

};


#endif //NOWTHISONEPLEASE_AVLTREES_H
