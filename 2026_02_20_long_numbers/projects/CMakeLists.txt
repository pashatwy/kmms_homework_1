cmake_minimum_required(VERSION 3.2...4.1)

project(2026_02_20_long_numbers)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(long_number)

set(CMAKE_SUPPRESS_REGENERATION true)