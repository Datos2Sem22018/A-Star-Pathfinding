cmake_minimum_required(VERSION 3.10)
project(AStar)

set(CMAKE_CXX_STANDARD 11)

add_executable(AStar main.cpp Location.cpp Location.h Node.cpp Node.h)