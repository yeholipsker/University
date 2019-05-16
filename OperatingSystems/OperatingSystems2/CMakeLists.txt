cmake_minimum_required(VERSION 3.7)
project(OperatingSystems2)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES ex2_inp.c)
set(SOURCE_FILES2 ex2_upd.c)
set(SOURCE_FILES3 ex2.c)
set(SOURCE_FILES_TEST ex2_inp_test.c)
add_executable(ex2_inp.out ${SOURCE_FILES})
add_executable(ex2_upd.out ${SOURCE_FILES2})
add_executable(ex2.out ${SOURCE_FILES3})
add_executable(ex2_inp_test.out ${SOURCE_FILES_TEST})