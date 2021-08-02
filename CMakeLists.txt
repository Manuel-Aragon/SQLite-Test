cmake_minimum_required(VERSION 3.8)

set(This Database)

project(${This} CXX C)

set(CMAKE_C_Standard 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POISITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    ${PROJECT_SOURCE_DIR}/include/sqlite3.h
    ${PROJECT_SOURCE_DIR}/include/Database.h
)

set(Sources
    ${PROJECT_SOURCE_DIR}/src/sqlite3.c
    ${PROJECT_SOURCE_DIR}/src/Database.cpp
)


add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)