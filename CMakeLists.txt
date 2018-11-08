cmake_minimum_required(VERSION 3.11)
project(TSPAlgorithmsComparison)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_BUILD_TYPE MATCHES RELEASE)
	set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif (CMAKE_BUILD_TYPE MATCHES RELEASE)

add_executable(TSPAlgorithmsComparison main.cpp Program.cpp Program.h TravellingSalesmanProblem.cpp TravellingSalesmanProblem.h BruteForce.cpp BruteForce.h BranchAndBound.cpp BranchAndBound.h Algorithm.cpp Algorithm.h Test.cpp Test.h)
