cmake_minimum_required(VERSION 3.31 FATAL_ERROR)

project(sim LANGUAGES C)

set(CMAKE_C_STANDARD            99)
set(CMAKE_C_STANDARD_REQUIRED   ON)
set(CMAKE_C_FLAGS               "-Wall")

add_subdirectory(lib)
add_subdirectory(extern)
add_subdirectory(project)
add_subdirectory(res)
