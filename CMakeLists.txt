
cmake_minimum_required (VERSION 2.8)
project (BnBTree)

set(CMAKE_CXX_FLAGS "-Wempty-body -Wall -Wno-sign-compare -std=c++0x -fdiagnostics-color=auto ${CMAKE_CXX_FLAGS}")

add_library (bnb bnbtree.cpp)
add_executable (bnbtest bnbtest.cpp bnbtree)



