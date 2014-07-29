
cmake_minimum_required (VERSION 2.8)
project (BnBTree)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS "-Wempty-body -Wall -Wno-sign-compare ${CMAKE_CXX_FLAGS}")

add_library (bnb SHARED bnbtree.cpp)
add_executable (bnbtest bnbtest.cpp bnbtree)



