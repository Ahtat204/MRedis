cmake_minimum_required(VERSION 3.30)
project(MRedis)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_BUILD_TYPE Release)
include_directories(include)

add_library(MRedis main.c)