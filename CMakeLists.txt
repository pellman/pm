cmake_minimum_required(VERSION 3.1)
project(pm)
set(CMAKE_CXX_STANDARD 14)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# = object libraries =
add_subdirectory("src")

# = full sources of each module=
set(sources_to_data
  ${part_data}
)
set(sources_to_grammar
  ${part_data}
  ${part_grammar}
  ${part_regex}
  ${part_set}
  ${part_stream}
)
set(sources_to_regex
  ${part_data}
  ${part_regex}
  ${part_stream}
)
set(sources_to_set
  ${part_data}
  ${part_set}
)
set(sources_to_stream
  ${part_stream}
)
set(sources_to_pm
  ${part_data}
  ${part_grammar}
  ${part_regex}
  ${part_set}
  ${part_stream}
)

# = libraries =
add_library(data EXCLUDE_FROM_ALL ${sources_to_data})
add_library(grammar EXCLUDE_FROM_ALL ${sources_to_grammar})
add_library(regex EXCLUDE_FROM_ALL ${sources_to_regex})
add_library(set EXCLUDE_FROM_ALL ${sources_to_set})
add_library(stream EXCLUDE_FROM_ALL ${sources_to_stream})

add_library(pm ${sources_to_pm})
