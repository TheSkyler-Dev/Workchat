cmake_minimum_required(VERSION 3.16.0)

cmake_policy(SET CMP0077 NEW)

project(Workchat VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20) # Corrected to C++20 (C++26 is not yet standardized)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

# FetchContent module to download dependencies
include(FetchContent)

# Fetch nlohmann/json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2 # Use the latest stable version or specify a version
)

FetchContent_MakeAvailable(nlohmann_json)

# Add sources
set(SOURCES
    main.cpp
)

add_executable(Workchat ${SOURCES})

# Link nlohmann/json to the target
target_link_libraries(Workchat PRIVATE nlohmann_json::nlohmann_json)

# Precompiled headers
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