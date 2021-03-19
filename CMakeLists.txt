cmake_minimum_required(VERSION 3.15)
project(NHF C)

set(CMAKE_C_STANDARD 99)

add_executable(NHF main.c econio.h econio.c read.c read.h generate.c generate.h print.c print.h datastruct.h my_time.c my_time.h logic.c logic.h)