cmake_minimum_required(VERSION 3.14)
project(Triangles)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(UnitTests unit_tests.cpp)

target_link_libraries(UnitTests ${GTEST_LIBRARIES} pthread)
