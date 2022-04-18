# GoogleTest requires at least C++11
cmake_minimum_required(VERSION 3.5)
project(atrix_test)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  matrix_test
  matrix_test.cpp
)

target_link_libraries(
  matrix_test 
  -g
  gtest_main
)

add_executable(
  vector_test
  vector_test.cpp
)

target_link_libraries(
  vector_test 
  -g
  gtest_main
)

add_executable(
  algorithms_test
  linalg/algorithms_test.cpp
)

target_link_libraries(
  algorithms_test 
  -g
  gtest_main
)

add_executable(
  decompositions_test
  linalg/decompositions_test.cpp
)

target_link_libraries(
  decompositions_test 
  -g
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(matrix_test)
gtest_discover_tests(vector_test)
gtest_discover_tests(algorithms_test)
gtest_discover_tests(decompositions_test)