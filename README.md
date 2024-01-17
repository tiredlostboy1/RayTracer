# Ray Tracing

to compile using cmake 
This is a C++ Ray Tracing project that utilizes the SDL2 library for graphical output. 

## Prerequisites 

Before compiling and running this project, ensure that you have the following dependencies installed: 

* C++ compiler
- SDL2 library 
* CMake 

## Installation 

To install SDL2, run the following command: 

``` 
sudo apt-get install libsdl2-dev
```

CMake

You can download and install CMake from the official website: https://cmake.org/download/ 

## Build Instructions

To compile the project using CMake, follow these steps:

1. Open a terminal and navigate to the project's root directory. 
2. Run the following command to generate the build files using CMake:
```
cmake -S . -B build
``` 
3. 	Change to the build directory: 
```
cd build
```
4.	Run the make command to build the project: 
```
make
``` 

## Running the Program 

After successfully building the project, you can run the Ray Tracer program.

Execute the following command from the project's root directory:
```
./RayTracer
```

The program will generate the rendered output based on the specified scene and display it using the SDL2 library.