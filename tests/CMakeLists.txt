cmake_minimum_required(VERSION 3.10)
project(test LANGUAGES CXX)

include_directories(../include)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME})

target_sources(
  ${PROJECT_NAME}

  PRIVATE
    buffer_matrix_test.cpp
)

target_link_libraries(
  ${PROJECT_NAME}

  PRIVATE
    gtest
    gtest_main
)