# Define the library target
add_library(Objects Objectbase.hpp Objectbase.cpp 
                    ObjSphere.hpp ObjSphere.cpp 
                    ObjectPlane.hpp ObjectPlane.hpp
                    ../Ray/Ray.hpp ../Ray/Ray.cpp 
                    ../Gtfm/Gtfm.hpp ../Gtfm/Gtfm.cpp)

include_directories(Ray)
include_directories(Gtfm)

# Include directories
target_include_directories(Objects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set any necessary compile options
target_compile_options(Objects PUBLIC -Wall -Wextra)
