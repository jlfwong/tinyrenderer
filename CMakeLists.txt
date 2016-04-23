cmake_minimum_required(VERSION 3.5)
project(tinyrenderer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/point3d.h
        src/point3d.cpp
        src/sdl_context_2d.cc
        src/sdl_context_2d.h
        src/third_party/tiny_obj_loader.cc
        src/third_party/tiny_obj_loader.h
        src/polygon3D.cc
        src/polygon3D.h
        src/geometry.cc
        src/geometry.h src/test_main.cc)

add_executable(tinyrenderer src/main.cc ${SOURCE_FILES})

find_package(sdl2 REQUIRED)
# SDL2_LIBARIES contains trailing whitespace when SDL was installed with homebrew. Without this strip, we see an error message looking like this:
# Target "tinyrenderer" links to item "-L/usr/local/Cellar/sdl2/2.0.4/lib
# -lSDL2 " which has leading or trailing whitespace.  This is now an error
# according to policy CMP0004.
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

target_include_directories(tinyrenderer PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(tinyrenderer ${SDL2_LIBRARIES})


##############
# Unit Tests
##############

set(TEST_FILES
        src/test_main.cc
        src/geometry_test.cc)

add_subdirectory(src/third_party/googletest)

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUnitTests ${SOURCE_FILES} ${TEST_FILES})

target_link_libraries(runUnitTests gtest gtest_main)
target_include_directories(runUnitTests PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(runUnitTests ${SDL2_LIBRARIES})
