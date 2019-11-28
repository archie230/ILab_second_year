cmake_minimum_required(VERSION 3.13)
project(search_tree)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(unittests tests/treeTests.cpp)

target_link_libraries(unittests ${GTEST_LIBRARIES} pthread)
