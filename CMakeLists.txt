cmake_minimum_required(VERSION 3.16)
project(IM3D)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output directory for the build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/alib)

# Add source files for the engine
file(GLOB_RECURSE SRC
    src/IM3D/*.cpp
    src/IM3D/*.c
)

# Define the Imagine3D library as a shared library
add_library(IM3D SHARED ${SRC}) #dll

# Specify include directories for the engine
target_include_directories(IM3D
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/include/imgui
)

# Set compile definitions for exporting symbols (for DLLs on Windows)
target_compile_definitions(IM3D
    PRIVATE IM3D_BUILD_DLL
    PUBLIC IM3D_PLATFORM_WINDOWS
    PUBLIC IM3D_DYNAMIC_LINK
)

# Link libraries
target_link_directories(IM3D PUBLIC vendor/lib)
target_link_libraries(IM3D PRIVATE opengl32 glfw3 assimp-vc143-mtd)