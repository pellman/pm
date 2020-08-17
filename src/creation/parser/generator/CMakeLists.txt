file(GLOB src_creation_parser_generator
  "*.cpp"
)
add_library(ol_creation_parser_generator OBJECT EXCLUDE_FROM_ALL
  ${src_creation_parser_generator}
)
set(part_creation_parser_generator
  $<TARGET_OBJECTS:ol_creation_parser_generator>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
