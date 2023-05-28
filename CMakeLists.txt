cmake_minimum_required(VERSION 3.0.0)
project(Italrecept VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wnull-dereference")

file(GLOB italrecept_SRC
     "src/*.h"
     "src/*.cpp"
)

add_executable(Italrecept ${italrecept_SRC})

add_definitions(-DMEMTRACE)
