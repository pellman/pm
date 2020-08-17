file(GLOB src_devel_char_set
  "*.cpp"
)
add_library(ol_devel_char_set OBJECT EXCLUDE_FROM_ALL
  ${src_devel_char_set}
)
set(part_devel_char_set
  $<TARGET_OBJECTS:ol_devel_char_set>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
