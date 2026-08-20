cmake_minimum_required(VERSION 3.20)
project(cpp_interpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(interpreter src/runtime.cpp)
target_include_directories(interpreter PUBLIC include)
target_compile_features(interpreter PUBLIC cxx_std_20)

if(MSVC)
  target_compile_options(interpreter PRIVATE /W4 /permissive-)
else()
  target_compile_options(interpreter PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(cpp-interpreter src/main.cpp)
target_link_libraries(cpp-interpreter PRIVATE interpreter)

include(CTest)
if(BUILD_TESTING)
  add_executable(interpreter-smoke tests/smoke.cpp)
  target_link_libraries(interpreter-smoke PRIVATE interpreter)
  add_test(NAME interpreter-smoke COMMAND interpreter-smoke)
endif()
