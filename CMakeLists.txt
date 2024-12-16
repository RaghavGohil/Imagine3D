# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(VoxelEngine LANGUAGES CXX C)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories (for GLAD, GLFW, etc.)
include_directories(vendor/include)

# Add custom library directory (path to where your custom libs are stored)
link_directories(vendor/lib)

# Add the source files
set(SOURCES
    src/glad.c
    src/main.cpp
    src/shader.cpp
    src/texture.cpp
)

# Create the executable
add_executable(VoxelEngine ${SOURCES})

# Link libraries
target_link_libraries(VoxelEngine PRIVATE opengl32 glfw3)
