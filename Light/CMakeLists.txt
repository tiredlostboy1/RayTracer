# Define the library target
add_library(Light LightBase.cpp LightBase.hpp PointLight.hpp PointLight.cpp
                        ../Ray/Ray.hpp ../Ray/Ray.cpp
                        ../Objects/Objectbase.hpp ../Objects/Objectbase.cpp)

include_directories(Ray)
include_directories(Objects)

# Include directories
target_include_directories(Light PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set any necessary compile options
target_compile_options(Light PUBLIC -Wall -Wextra)
