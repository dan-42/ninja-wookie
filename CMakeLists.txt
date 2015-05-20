cmake_minimum_required(VERSION 2.8.0)
project(ninja-wookie)

set(CMAKE_BUILD_TYPE "DEBUG")
#set(CMAKE_BUILD_TYPE "RELEASE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS "-O3 ") 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(src)
