
cmake_minimum_required (VERSION 2.8)
project (BnBTree)

add_library (bnbtree SHARED bnbtree.cpp)
add_executable (bnbtest bnbtest.cpp)



