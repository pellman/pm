cmake_minimum_required(VERSION 3.1)
project(pm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# interface libraries + their features
add_subdirectory("type_abuse")
add_subdirectory("utils")

# object libraries; all use features of interface libraries
add_subdirectory("dataset")
add_subdirectory("grammar")
add_subdirectory("regexp")
add_subdirectory("stream")

# STANDALONE LIBRARY dataset
add_library(dataset
  $<TARGET_OBJECTS:dataset_ol>
  dummy.cpp
)

# STANDALONE LIBRARY grammar
add_library(grammar
  $<TARGET_OBJECTS:grammar_ol>
  $<TARGET_OBJECTS:regexp_ol>
  $<TARGET_OBJECTS:dataset_ol>
  $<TARGET_OBJECTS:stream_ol>
  dummy.cpp
)

# STANDALONE LIBRARY regexp
add_library(regexp
  $<TARGET_OBJECTS:regexp_ol>
  $<TARGET_OBJECTS:stream_ol>
  dummy.cpp
)

# STANDALONE LIBRARY stream
add_library(stream
  $<TARGET_OBJECTS:stream_ol>
  dummy.cpp
)

# WHOLE LIBRARY pm
add_library(pm
  $<TARGET_OBJECTS:grammar_ol>
  $<TARGET_OBJECTS:regexp_ol>
  $<TARGET_OBJECTS:dataset_ol>
  $<TARGET_OBJECTS:stream_ol>
  dummy.cpp
)
