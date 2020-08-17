add_subdirectory("generator")

file(GLOB src_creation_parser_base
  "*.cpp"
)
add_library(ol_creation_parser_base OBJECT EXCLUDE_FROM_ALL
  ${src_creation_parser_base}
)
set(part_creation_parser_base
  $<TARGET_OBJECTS:ol_creation_parser_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
set(part_creation_parser
  ${part_creation_parser_base}
  ${part_creation_parser_generator}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
