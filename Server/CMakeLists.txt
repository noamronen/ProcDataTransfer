cmake_minimum_required(VERSION 3.20)
project(ProcDataTransfer)

set(CMAKE_CXX_STANDARD 14)

add_executable(ProcDataTransfer main.cpp Server.h Server.cpp Procfs_Miner.h Procfs_Miner.cpp)

SET(CMAKE_CXX_FLAGS -pthread)
