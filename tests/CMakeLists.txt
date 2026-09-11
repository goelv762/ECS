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

include(GoogleTest)

add_executable(ecs_tests
    entity.cc
    component.cc
	system.cc
)

target_link_libraries(ecs_tests
    PRIVATE
	ecs
	GTest::gtest_main
)

gtest_discover_tests(ecs_tests)
