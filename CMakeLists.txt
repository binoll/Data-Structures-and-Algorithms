cmake_minimum_required(VERSION 3.25)
project(Data-Structures-and-Algorithms)

set(CMAKE_CXX_STANDARD 14)

add_executable(Data-Structures-and-Algorithms main.cpp "data_structures/set.h" "data_structures/trees/BST.h" "libs.h" data_structures/trees/AVL.h)
