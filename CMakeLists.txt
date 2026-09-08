cmake_minimum_required(VERSION 4.4)
project(ecs)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_LINKER_TYPE MOLD)

add_subdirectory(tests)
add_subdirectory(ecs)

enable_testing()
