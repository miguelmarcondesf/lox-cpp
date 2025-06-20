cmake_minimum_required(VERSION 4.0)

project(lox-cpp VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(lox-cpp src/main.cpp)
