# Define the library target
add_library(Ray Ray.cpp Ray.hpp)

# Include directories
target_include_directories(Ray PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set any necessary compile options
target_compile_options(Ray PUBLIC -Wall -Wextra)
