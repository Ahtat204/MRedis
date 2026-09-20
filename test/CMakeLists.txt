find_package(PkgConfig REQUIRED)
pkg_check_modules(CRITERION REQUIRED IMPORTED_TARGET criterion)
set(CMAKE_BUILD_TYPE Debug)
# Cleaned up: Removed the duplicate file compilation since it's inside MRedis
add_executable(mredis_tests ringbuffer.test.c)

target_link_libraries(mredis_tests
        PRIVATE
        MRedis
        PkgConfig::CRITERION
)

# Corrected the COMMAND to match your executable target name
add_test(NAME ringbuffer_tests COMMAND mredis_tests)
# Add this right after defining your test executable
target_compile_options(mredis_tests PRIVATE -g -O0)
