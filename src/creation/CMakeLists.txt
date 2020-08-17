add_subdirectory("char_set")
add_subdirectory("parser")

set(part_creation
  ${part_creation_char_set}
  ${part_creation_parser}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
