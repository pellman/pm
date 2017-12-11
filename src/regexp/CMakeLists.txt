add_subdirectory("expressions")

file(GLOB src_regexp_base
  "*.cpp"
)
add_library(ol_regexp_base OBJECT EXCLUDE_FROM_ALL
  ${src_regexp_base}
)
set(part_regexp_base
  $<TARGET_OBJECTS:ol_regexp_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
set(part_regexp
  ${part_regexp_base}
  ${part_regexp_expressions}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
