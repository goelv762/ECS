# due to being header only, the ecs will be accessed as an interface (ae2 me interface mentioned)
add_library(ecs INTERFACE)
add_library(ecs::ecs ALIAS ecs)

target_include_directories(ecs INTERFACE ${CMAKE_SOURCE_DIR}/..)
target_compile_features(ecs INTERFACE cxx_std_20)
