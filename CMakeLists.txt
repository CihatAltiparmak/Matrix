cmake_minimum_required(VERSION 3.5)

project(atrix)

add_library(atrix SHARED
    src/matrix.h
    src/matrix.cpp
    src/vector.h
    src/vector.cpp
    src/linalg/algorithms.h
    src/linalg/algorithms.cpp
    src/linalg/decompositions.h
    src/linalg/decompositions.cpp
)

install (TARGETS atrix 
    DESTINATION lib)

install (DIRECTORY ${PROJECT_SOURCE_DIR}/src/
    DESTINATION include/atrix
    PATTERN "src/*"
)
