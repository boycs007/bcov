cmake_minimum_required(VERSION 3.10)
project(bcov LANGUAGES C CXX)

add_library(bcov STATIC bcov.cpp)
target_include_directories(bcov PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})