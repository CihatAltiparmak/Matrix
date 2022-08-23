cmake_minimum_required(VERSION 3.5)

project(atrix)

add_library(atrix SHARED
    matrix.h
    matrix.cpp
    vector.h
    vector.cpp
    linalg/algorithms.h
    linalg/algorithms.cpp
    linalg/decompositions.h
    linalg/decompositions.cpp
    linalg/utils.h 
    linalg/utils.cpp
    errors.h
)

install (TARGETS atrix 
    DESTINATION lib)

install (DIRECTORY ${PROJECT_SOURCE_DIR}/
    DESTINATION include/atrix
)