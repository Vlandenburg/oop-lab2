cmake_minimum_required(VERSION 3.14)

project(eleven_arithmetic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

add_executable(main_app main.cpp src/lab2.cpp)
target_include_directories(main_app PRIVATE include)

add_executable(run_tests 
    tests/main_test.cpp 
    tests/eleven_test.cpp 
    src/lab2.cpp
)
target_include_directories(run_tests PRIVATE include)
target_link_libraries(run_tests PRIVATE gtest_main)

enable_testing()
add_test(NAME ElevenClassTests COMMAND run_tests)