cmake_minimum_required(VERSION 3.22)
project(NowThisOnePlease)

set(CMAKE_CXX_STANDARD 14)

include_directories(Trees)

add_executable(NowThisOnePlease
        Trees/BinarySearchTrees.cpp
        Trees/BinarySearchTrees.h
        Trees/BST_test.cpp
        Trees/AVLTrees.cpp
        Trees/AVLTrees.h
        Trees/AVL_test.cpp)
