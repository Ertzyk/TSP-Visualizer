cmake_minimum_required(VERSION 3.15)
project(TSP-Visualizer VERSION 1.0.0 LANGUAGES CXX)

# Enforce C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

# Find required external libraries (Note the Capitalized components for SFML 3.0)
find_package(SFML 3.0.0 COMPONENTS Graphics Window System REQUIRED)
find_package(CURL REQUIRED)

# Recursively grab all .cpp files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create the main executable
add_executable(tsp_visualizer ${SOURCES})

# Add 'src' as an include directory so `#include "external/nlohmann/json.hpp"` works perfectly
target_include_directories(tsp_visualizer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Link the libraries to the executable
target_link_libraries(tsp_visualizer 
    PRIVATE 
        SFML::Graphics 
        SFML::Window 
        SFML::System 
        CURL::libcurl
)