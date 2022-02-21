cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(GraphC++)

SET(INCLUDE_DIR                  "${CMAKE_CURRENT_LIST_DIR}/include")
SET(BIN_DIR                      "${CMAKE_CURRENT_LIST_DIR}/bin")


SET(TEST_SRC_DIR                 ${CMAKE_CURRENT_LIST_DIR})

SET(TEST_HEADER_FILES            ${INCLUDE_DIR})
INCLUDE_DIRECTORIES(             ${TEST_HEADER_FILES})

set(CMAKE_CXX_FLAGS              "${CMAKE_CXX_FLAGS} -std=c++17")
SET(CMAKE_CXX_FLAGS_RELEASE      "-O3 -fopenmp -funroll-loops -march=native -mtune=native ")
set(CMAKE_CXX_FLAGS_DEBUG        "-g")

add_subdirectory(tests)
