add_subdirectory("expressions")
add_subdirectory("utils")

file(GLOB src_regex_base
  "*.cpp"
)
add_library(ol_regex_base OBJECT EXCLUDE_FROM_ALL
  ${src_regex_base}
)
set(part_regex_base
  $<TARGET_OBJECTS:ol_regex_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
set(part_regex
  ${part_regex_base}
  ${part_regex_expressions}
  ${part_regex_utils}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
