file(GLOB src_creation_char_set
  "*.cpp"
)
add_library(ol_creation_char_set OBJECT EXCLUDE_FROM_ALL
  ${src_creation_char_set}
)
set(part_creation_char_set
  $<TARGET_OBJECTS:ol_creation_char_set>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
