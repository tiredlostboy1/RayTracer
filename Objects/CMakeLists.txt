# Define the library target
add_library(Objects Objectbase.hpp Objectbase.cpp ObjSphere.hpp ObjSphere.cpp ../Ray/Ray.hpp ../Ray/Ray.cpp)

include_directories(Ray)

# Include directories
target_include_directories(Objects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set any necessary compile options
target_compile_options(Objects PUBLIC -Wall -Wextra)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

# Add the include directories for SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# Link against the SDL2 library
target_link_libraries(Objects ${SDL2_LIBRARIES})