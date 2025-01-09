# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(Imagine3D LANGUAGES CXX C)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories (for GLAD, GLFW, etc.)
include_directories(vendor/include vendor/include/imgui)

# Add custom library directory (path to where your custom libs are stored)
link_directories(vendor/lib)

file(GLOB_RECURSE SRC
    src/*.cpp 
    src/*.c
)

# Create the executable
add_executable(Imagine3D ${SRC})

# Link libraries
target_link_libraries(Imagine3D PRIVATE opengl32 glfw3 assimp-vc143-mtd)
