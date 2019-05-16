cmake_minimum_required(VERSION 3.7)
project(untitled)

set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES ex41.c)
set(SOURCE_FILES2 ex42.c)
add_executable(ex41.out ${SOURCE_FILES})
add_executable(ex42.out ${SOURCE_FILES2})

target_link_libraries(ex42.out -lpthread)
