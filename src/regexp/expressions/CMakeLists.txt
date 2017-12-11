add_subdirectory("composition")
add_subdirectory("functions")
add_subdirectory("terminals")

file(GLOB src_regexp_expressions_special
  "*.cpp"
)
add_library(ol_regexp_expressions_special OBJECT EXCLUDE_FROM_ALL
  ${src_regexp_expressions_special}
)
set(part_regexp_expressions_special
  $<TARGET_OBJECTS:ol_regexp_expressions_special>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
set(part_regexp_expressions
  ${part_regexp_expressions_composition}
  ${part_regexp_expressions_functions}
  ${part_regexp_expressions_special}
  ${part_regexp_expressions_terminals}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
