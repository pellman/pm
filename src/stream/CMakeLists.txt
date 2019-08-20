add_subdirectory("utils")

file(GLOB src_stream_base
  "*.cpp"
)
add_library(ol_stream_base OBJECT EXCLUDE_FROM_ALL
  ${src_stream_base}
)
set(part_stream_base
  $<TARGET_OBJECTS:ol_stream_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
set(part_stream
  ${part_stream_base}
  ${part_stream_utils}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
