cmake_minimum_required(VERSION 3.2...4.1)

project(2025_12_16_my_project)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(shell_sort)
add_subdirectory(obychaika)
add_subdirectory(tests)

set(CMAKE_SUPPRESS_REGENERATION true)