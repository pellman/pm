file(GLOB src_devel_parser
  "*.cpp"
)
add_library(ol_devel_parser OBJECT EXCLUDE_FROM_ALL
  ${src_devel_parser}
)
set(part_devel_parser
  $<TARGET_OBJECTS:ol_devel_parser>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
