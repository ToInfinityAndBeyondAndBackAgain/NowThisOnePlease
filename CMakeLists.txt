cmake_minimum_required(VERSION 3.22)
project(NowThisOnePlease)

set(CMAKE_CXX_STANDARD 14)

include_directories(BinarySearchFun)

add_executable(NowThisOnePlease
        BinarySearchFun/BinarySearchTrees.cpp
        BinarySearchFun/BinarySearchTrees.h
        BinarySearchFun/BST_test.cpp)
