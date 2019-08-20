add_subdirectory("flow")
add_subdirectory("terminal")

file(GLOB src_regex_expressions_base
  "*.cpp"
)
add_library(ol_regex_expressions_base OBJECT EXCLUDE_FROM_ALL
  ${src_regex_expressions_base}
)
set(part_regex_expressions_base
  $<TARGET_OBJECTS:ol_regex_expressions_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)

set(part_regex_expressions
  ${part_regex_expressions_base}
  ${part_regex_expressions_flow}
  ${part_regex_expressions_terminal}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
