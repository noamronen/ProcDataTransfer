cmake_minimum_required(VERSION 3.20)
project(ProcDataTransferClient)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProcDataTransferClient main.cpp Client.h Client.cpp)

SET(CMAKE_CXX_FLAGS -pthread)
