cmake_minimum_required(VERSION 3.12)
project(TspOptimization)

set(CMAKE_CXX_STANDARD 17)

add_executable(TspOptimization source/main.cpp source/GeneticAlgorithm.cpp headers/GeneticAlgorithm.h source/CostFunction.cpp headers/CostFunction.h source/DataSet.cpp headers/DataSet.h source/RandomSearch.cpp headers/RandomSearch.h)