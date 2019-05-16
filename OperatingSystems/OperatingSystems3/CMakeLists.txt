cmake_minimum_required(VERSION 3.7)
project(OperatingSystems3)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES ex31.c)
set(SOURCE_FILES2 ex32.c)
set(SOURCE_FILES3 tests.c)
add_executable(ex31.out ${SOURCE_FILES})
add_executable(ex32.out ${SOURCE_FILES2})
add_executable(tests.out ${SOURCE_FILES3})