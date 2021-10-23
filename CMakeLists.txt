cmake_minimum_required(VERSION 3.10)

# set the project name
project(Perli_Islands)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# set include dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

# find and include sdl2 files
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# set cflags
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# set cpp standard
set(CMAKE_CXX_STANDARD 14)

# add the executable
add_executable(Perli_Islands.run src/main.cpp src/render.cpp)

# link sdl2
target_link_libraries(Perli_Islands.run ${SDL2_LIBRARIES})