
cmake_minimum_required (VERSION 2.8)
project (BnBTree)

set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS "-Wempty-body -Wall -Wno-sign-compare ${CMAKE_CXX_FLAGS}")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)




