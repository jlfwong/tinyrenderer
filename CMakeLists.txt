cmake_minimum_required(VERSION 3.5)
project(tinyrenderer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/main.cc)

add_executable(tinyrenderer ${SOURCE_FILES})

find_package(sdl2 REQUIRED)
# SDL2_LIBARIES contains trailing whitespace when SDL was installed with homebrew. Without this strip, we see an error message looking like this:
# Target "tinyrenderer" links to item "-L/usr/local/Cellar/sdl2/2.0.4/lib
# -lSDL2 " which has leading or trailing whitespace.  This is now an error
# according to policy CMP0004.
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

target_include_directories(tinyrenderer PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(tinyrenderer ${SDL2_LIBRARIES})

