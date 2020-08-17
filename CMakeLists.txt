cmake_minimum_required(VERSION 3.8)
project(pm)
set(CMAKE_CXX_STANDARD 17)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# = object libraries =
add_subdirectory("src")

# = sources =
# see target "all_parts" in "src" subdirectory

# = libraries =
add_library(pm ${all_parts})
