cmake_minimum_required(VERSION 3.10)
project(GROUP9_ML1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Tell the compiler where to find header files
include_directories(include)

# Stitch the source files together into an executable
add_executable(ml_project src/main.cpp src/ml_pipeline.cpp)
