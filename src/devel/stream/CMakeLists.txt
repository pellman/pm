file(GLOB src_devel_stream
  "*.cpp"
)
add_library(ol_devel_stream OBJECT EXCLUDE_FROM_ALL
  ${src_devel_stream}
)
set(part_devel_stream
  $<TARGET_OBJECTS:ol_devel_stream>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
