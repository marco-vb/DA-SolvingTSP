cmake_minimum_required(VERSION 3.23)
project(tsp)

set(CMAKE_CXX_STANDARD 23)

add_executable(tsp main.cpp ds/Heap.h ds/Graph.cpp ds/Graph.h)
