# No need for cmake_minimum_required or project() down here
add_library(MRedis
        main.c
        resp.c
        ringbuffer.c
        ringbuffer.h
        resp.h
)

# Best practice: link include directories directly to the target 
# instead of globally using include_directories()
target_include_directories(MRedis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
