# Define the library target
add_library(Ray Ray.cpp Ray.hpp)

# Include directories
target_include_directories(Ray PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set any necessary compile options
target_compile_options(Ray PUBLIC -Wall -Wextra)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

# Add the include directories for SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# Link against the SDL2 library
target_link_libraries(Ray ${SDL2_LIBRARIES})