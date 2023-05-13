cmake_minimum_required(VERSION 3.10)

project(RayTracer)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

# Add the include directories for SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# Add subdirectories
add_subdirectory(CApp)
add_subdirectory(Image)
add_subdirectory(Scene)

# Define the executable target
add_executable(RayTracer main.cpp)

# Link against the libraries from subdirectories
target_link_libraries(RayTracer ${SDL2_LIBRARIES} CApp Image Scene)

# The executable is in source dir
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}")