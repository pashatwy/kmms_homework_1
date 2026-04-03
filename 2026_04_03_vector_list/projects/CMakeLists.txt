cmake_minimum_required(VERSION 3.2...4.1)

project(2026_04_03_vector_list)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(vector_list)

set(CMAKE_SUPPRESS_REGENERATION true)