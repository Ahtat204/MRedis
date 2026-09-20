cmake_minimum_required(VERSION 3.30)
project(MRedis LANGUAGES C) # Set the project language globally here

set(CMAKE_BUILD_TYPE Release)

# Automatically creates the BUILD_TESTING option and calls enable_testing()
include(CTest)

# Add production source code directory
add_subdirectory(src)

# Conditionally include tests
if (BUILD_TESTING)
    add_subdirectory(test)
endif()
