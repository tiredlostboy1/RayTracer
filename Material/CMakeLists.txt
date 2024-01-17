# Define the library target
add_library(Material MaterialBase.cpp MaterialBase.hpp
SimpleMaterial.hpp SimpleMaterial.cpp 
../Ray/Ray.hpp ../Ray/Ray.cpp
../Objects/Objectbase.hpp ../Objects/Objectbase.cpp)

# Include directories
target_include_directories(Scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(Objects)
include_directories(Light)
include_directories(Ray)

# Set any necessary compile options
target_compile_options(Material PUBLIC -Wall -Wextra)
