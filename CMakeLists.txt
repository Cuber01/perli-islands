cmake_minimum_required(VERSION 3.10)

# set the project name
project(Perli_Islands)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# find and include sdl2 files
find_package(SDL2 REQUIRED)

# set include dirs
include_directories(${SDL2_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include/ /usr/include/ ${CMAKE_CURRENT_SOURCE_DIR}/lib/noiseutils/)

# set compile debug flags
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# set cpp standard
set(CMAKE_CXX_STANDARD 14)

# add the executable
add_executable(Perli_Islands.run src/main.cpp src/render.cpp lib/noiseutils/noiseutils.cpp)

# link sdl2
target_link_libraries(Perli_Islands.run ${SDL2_LIBRARIES} noise)