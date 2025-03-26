cmake_minimum_required(VERSION 3.16.0)

project(Workchat VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCES
    main.cpp
)

add_executable(Workchat ${SOURCES})

target_precompile_headers(Workchat PRIVATE
    <iostream>
    <string>
)

if(MSVC)
  target_compile_options(Workchat PRIVATE /W4)
else()
  target_compile_options(Workchat PRIVATE -Wall -Wextra -Wpedantic)
endif()

install(TARGETS Workchat DESTINATION bin)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Include directories: ${PROJECT_SOURCE_DIR}/include")