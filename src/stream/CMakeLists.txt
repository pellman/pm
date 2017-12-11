file(GLOB src_stream
  "*.cpp"
)
add_library(ol_stream OBJECT EXCLUDE_FROM_ALL
  ${src_stream}
)
set(part_stream
  $<TARGET_OBJECTS:ol_stream>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
