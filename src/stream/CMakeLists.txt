add_library(stream_ol OBJECT
  buffer.cpp
  stream.cpp
)
set(stream_source_features
  cxx_auto_type
)
set(stream_header_features
  cxx_deleted_functions
  cxx_rvalue_references
)
target_compile_features(stream_ol PRIVATE
  ${stream_source_features}
)
target_compile_features(stream_ol PUBLIC
  ${stream_header_features}
)
