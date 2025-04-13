include(FetchContent)

set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.16.0  # Use a specific release for stability
)

set(BUILD_GMOCK OFF)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_parser
                test.cpp
                "${PROJECT_SOURCE_DIR}/src/lexer.cpp"
                "${PROJECT_SOURCE_DIR}/src/ast.cpp"
)

target_include_directories(test_parser PUBLIC
                "${PROJECT_SOURCE_DIR}/src"
)

target_link_libraries(test_parser PRIVATE GTest::gtest)

include(GoogleTest)
gtest_discover_tests(test_parser)

# https://cmake.org/cmake/help/latest/guide/tutorial/Adding%20a%20Library.html
