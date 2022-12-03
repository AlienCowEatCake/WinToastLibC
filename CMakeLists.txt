cmake_minimum_required(VERSION 3.15)

project(WinToastLibC LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
    wintoastlibc
    SHARED
    ${CMAKE_CURRENT_LIST_DIR}/src/wintoastlib.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/wintoastlib.h
    ${CMAKE_CURRENT_LIST_DIR}/src/wintoastlibc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/wintoastlibc.h
)
target_link_libraries(
    wintoastlibc
    shlwapi
    user32
    advapi32
    ole32
)
set_target_properties(
    wintoastlibc
    PROPERTIES
    PUBLIC_HEADER
    "${CMAKE_CURRENT_LIST_DIR}/src/wintoastlibc.h"
    MSVC_RUNTIME_LIBRARY
    "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

add_library(
    wintoastlibc_static
    STATIC
    ${CMAKE_CURRENT_LIST_DIR}/src/wintoastlib.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/wintoastlib.h
    ${CMAKE_CURRENT_LIST_DIR}/src/wintoastlibc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/wintoastlibc.h
)
target_compile_definitions(
    wintoastlibc_static
    PUBLIC
    WTLC_BUILD_STATIC
)
target_link_libraries(
    wintoastlibc_static
    shlwapi
    user32
    advapi32
    ole32
)
set_target_properties(
    wintoastlibc_static
    PROPERTIES
    PUBLIC_HEADER
    "${CMAKE_CURRENT_LIST_DIR}/src/wintoastlibc.h"
)

add_executable(
    example1
    WIN32
    ${CMAKE_CURRENT_LIST_DIR}/example/example1.c
)
target_include_directories(
    example1
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)
target_link_libraries(
    example1
    wintoastlibc
    ole32
)

add_executable(
    example2
    WIN32
    ${CMAKE_CURRENT_LIST_DIR}/example/example2.c
)
target_include_directories(
    example2
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)
target_link_libraries(
    example2
    wintoastlibc_static
    shlwapi
    ole32
)

install(
    TARGETS wintoastlibc wintoastlibc_static example1 example2
    RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/install/bin
    ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/install/lib
    LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/install/lib
    PUBLIC_HEADER DESTINATION ${CMAKE_BINARY_DIR}/install/include
)
