cmake_minimum_required(VERSION 3.12)
project(crawler_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest CONFIG REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# create test executable
file(GLOB_RECURSE ALL_TESTS "*test_*.cpp")
add_executable(crawler_test ${ALL_TESTS})
target_link_libraries(crawler_test PRIVATE libcrawl GTest::gtest GTest::gtest_main)

add_test(NAME crawler_test COMMAND crawler_test)

# file(GLOB_RECURSE ALL_TESTS "*test_*.cpp")
# foreach(TEST ${ALL_TESTS})
#     get_filename_component(TEST_NAME ${TEST} NAME_WE)
#     message(STATUS "Adding test: ${TEST_NAME}")
#     add_executable(${TEST_NAME} ${TEST})
#     target_link_libraries(${TEST_NAME} PRIVATE libcrawl GTest::gtest GTest::gtest_main)
#     add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
# endforeach(TEST)
