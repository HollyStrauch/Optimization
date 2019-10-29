cmake_minimum_required(VERSION 3.13)
project(SRC C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(mt19937ar.sep)

add_executable(SRC
        MT/mt19937ar.c
        MT/mt19937ar.h
        fillrand.c
        fillrand.h
        ftnInput.c
        ftnInput.h
        Ftns.c
        ftnslst.h
        main.c
        matrixgen.c
        matrixgen.h
        run.c
        run.h)
