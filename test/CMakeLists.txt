# Find the Criterion package on the local system
find_package(PkgConfig REQUIRED)
pkg_check_modules(CRITERION REQUIRED criterion)

# Create the test executable
add_executable(test_suite ringbuffer.test.c)

# Link the implementation library and Criterion
target_link_libraries(test_suite
        PRIVATE
        math_utils
        ${CRITERION_LIBRARIES}
)

# Include Criterion header directories
target_include_directories(test_suite PRIVATE ${CRITERION_INCLUDE_DIRS})

# Register the executable as an official CTest case
add_test(NAME math_unit_tests COMMAND test_suite)