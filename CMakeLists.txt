cmake_minimum_required(VERSION 3.10)

project(crawler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ----------------- libcrawl -----------------

find_package(CURL REQUIRED)

file(GLOB_RECURSE LIBRARY_SOURCES "src/libcrawl/*.h" "src/libcrawl/*.cpp")
add_library(libcrawl ${LIBRARY_SOURCES})
include_directories(src)
target_include_directories(libcrawl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(libcrawl PRIVATE CURL::libcurl)

# ----------------- runner -----------------

add_executable(crawler_runner src/runner.cpp)
target_link_libraries(crawler_runner libcrawl)

# ----------------- tests -----------------

add_subdirectory(test)