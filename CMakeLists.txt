# cmake_minimum_required(VERSION <specify CMake version here>)
project(Wet02)

set(CMAKE_CXX_STANDARD 14)

add_executable(Wet02 main.cpp UnionFind.cpp UnionFind.h DynamicArray.h AVLRankedNode.h AVLRankedTree.h AVLRankedNode.cpp AVLRankedTree.cpp DSW.cpp DSW.h Agency.cpp Agency.h TypeId.cpp TypeId.h TypeIdById.cpp TypeIdById.h)