cmake_minimum_required(VERSION 3.29)
project(Sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2")

add_executable(Sandbox src/main.cpp
        src/sandbox.h
        src/sandbox.cpp)
