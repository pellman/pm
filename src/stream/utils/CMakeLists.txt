file(GLOB src_stream_utils
  "*.cpp"
)
add_library(ol_stream_utils OBJECT EXCLUDE_FROM_ALL
  ${src_stream_utils}
)
set(part_stream_utils
  $<TARGET_OBJECTS:ol_stream_utils>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
