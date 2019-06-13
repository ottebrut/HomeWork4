cmake_minimum_required(VERSION 3.10)
project(lib)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_LIB huffman.cpp tree.cpp)
set(HEADER_LIB huffman.h tree.h)

add_library(lib STATIC ${SOURCE_LIB} ${HEADER_LIB})

add_executable(huffman_test huffman_test.cpp
        gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc)
target_link_libraries(huffman_test lib -pthread)
