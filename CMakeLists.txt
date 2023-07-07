cmake_minimum_required(VERSION 3.20)

project(juce-vitro VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    #DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_subdirectory(JUCE)
add_subdirectory(VITRO)
add_subdirectory(tests)
add_subdirectory(viewer)
