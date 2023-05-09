cmake_minimum_required(VERSION 3.10)

project(raytracer)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

# Add the include directories for SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# Add the executable target
add_executable(raytracer main.cpp CApp.cpp CApp.hpp)

# Link against the SDL2 library
target_link_libraries(raytracer ${SDL2_LIBRARIES})

# The executable is in source dir
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}")
