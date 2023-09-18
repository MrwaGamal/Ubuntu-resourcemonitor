#created by Marwa Gamal
cmake_minimum_required(VERSION 3.10)

project(ResourceMonitor)

# Add your source file(s) to the project
add_executable(resource_monitor src/main.cpp)


# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find and link necessary libraries (none required for this code)
# If you need additional libraries, add them here.

# Generate the Ninja build files
set(CMAKE_MAKE_PROGRAM "ninja")
