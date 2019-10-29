cmake_minimum_required(VERSION 3.14)
project(search_tree)

set(CMAKE_CXX_STANDARD 17)

#add_executable(time_test AVL_tree.hpp search_tree.hpp timetests/time_tests.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(AVL_unittests tests/AVL_treeTests.cpp)

target_link_libraries(AVL_unittests ${GTEST_LIBRARIES} pthread)
