# Define the library target
add_library(Scene Scene.cpp Scene.hpp 
            ../Camera/Camera.cpp ../Camera/Camera.hpp 
            ../Image/Image.hpp ../Image/Image.cpp 
            ../Objects/ObjSphere.hpp ../Objects/ObjSphere.cpp
            ../Objects/ObjectPlane.hpp ../Objects/ObjectPlane.cpp
            ../Light/PointLight.hpp ../Light/PointLight.cpp)

# Include directories
target_include_directories(Scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(Image)
include_directories(Camera)

# Set any necessary compile options
target_compile_options(Scene PUBLIC -Wall -Wextra)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

# Add the include directories for SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# Link against the SDL2 library
target_link_libraries(Scene ${SDL2_LIBRARIES})