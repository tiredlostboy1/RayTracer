# Define the library target
add_library(CApp CApp.cpp CApp.hpp)

# Include directories
target_include_directories(CApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set any necessary compile options
target_compile_options(CApp PUBLIC -Wall -Wextra)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

# Add the include directories for SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# Link against the SDL2 library
target_link_libraries(CApp ${SDL2_LIBRARIES})