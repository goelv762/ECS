cmake_minimum_required(VERSION 3.24)
project(ecs)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_LINKER_TYPE MOLD)

add_subdirectory(ecs)
add_subdirectory(test)
