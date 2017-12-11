cmake_minimum_required(VERSION 3.1)
project(pm)
set(CMAKE_CXX_STANDARD 11)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# = object libraries =
add_subdirectory("src")

# = full sources of each module=
set(sources_to_dataset
  ${part_dataset}
  ${part_type_abuse}
)
set(sources_to_grammar
  ${part_dataset}
  ${part_grammar}
  ${part_regexp}
  ${part_stream}
  ${part_type_abuse}
)
set(sources_to_regexp
  ${part_regexp}
  ${part_stream}
  ${part_type_abuse}
)
set(sources_to_stream
  ${part_stream}
)
set(sources_to_type_abuse
  ${part_type_abuse}
)
set(sources_to_pm
  ${part_dataset}
  ${part_grammar}
  ${part_regexp}
  ${part_stream}
  ${part_type_abuse}
)

# = libraries =
add_library(dataset EXCLUDE_FROM_ALL ${sources_to_dataset})
add_library(grammar EXCLUDE_FROM_ALL ${sources_to_grammar})
add_library(regexp EXCLUDE_FROM_ALL ${sources_to_regexp})
add_library(stream EXCLUDE_FROM_ALL ${sources_to_stream})
add_library(type_abuse EXCLUDE_FROM_ALL ${sources_to_type_abuse})
add_library(pm ${sources_to_pm})
