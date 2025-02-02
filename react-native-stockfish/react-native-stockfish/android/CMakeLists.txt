cmake_minimum_required(VERSION 3.4.1)
project(Stockfish)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 14)

add_library(react-native-stockfish            SHARED
            ../cpp/react-native-stockfish.cpp
            cpp-adapter.cpp
)

# Specifies a path to native header files.
include_directories(
            ../cpp
)
