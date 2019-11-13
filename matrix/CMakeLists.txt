cmake_minimum_required(VERSION 3.11)
project(matrix)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(UnitTests unit_tests/unit_tests.cpp)
target_link_libraries(UnitTests ${GTEST_LIBRARIES} pthread)