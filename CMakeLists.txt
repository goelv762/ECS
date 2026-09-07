cmake_minimum_required(VERSION 4.4)
project(ecs)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_LINKER_TYPE MOLD)

# gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  # the reason we point directly to the latest hash is for maximum reproducability (prevents updates from breaking tests)
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# for silly windows users
# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(ecs)

enable_testing()

add_executable(
  main_test
  main_test.cc
)
target_link_libraries(
  main_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(main_test)
