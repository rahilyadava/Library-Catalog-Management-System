# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(LibraryCatalogManagementSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(Header Files)

# Add executable with source files
add_executable(LibraryCatalogManagementSystem 
    main.cpp
    Source Files/Book.cpp
)

# Add custom headers if needed
include_directories(
    "Header Files"
)