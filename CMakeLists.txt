cmake_minimum_required(VERSION 3.30)
project(MRedis)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_BUILD_TYPE Release)
include_directories(src)
if (BUILD_TESTING)
    add_subdirectory(test)
endif ()
include(CTest)
add_library(MRedis src/main.c
        src/resp.c
        src/ringbuffer.c
        src/ringbuffer.h
        test/ringbuffer.test.c)
