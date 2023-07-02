cmake_minimum_required(VERSION 3.20)

project(juce-vitro VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(JUCE)
add_subdirectory(VITRO)

add_subdirectory(src)
