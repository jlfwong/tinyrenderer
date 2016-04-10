cmake_minimum_required(VERSION 3.5)
project(tinyrenderer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/main.cc)

find_package(sdl)
add_executable(tinyrenderer ${SOURCE_FILES})
include_directories(${SDL2_INCLUDE_DIR})
link_libraries(${SDL2_LIBRARY})

