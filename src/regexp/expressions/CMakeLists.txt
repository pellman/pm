add_subdirectory("flow")
add_subdirectory("functional")
add_subdirectory("terminal")

set(part_regexp_expressions
  ${part_regexp_expressions_flow}
  ${part_regexp_expressions_functional}
  ${part_regexp_expressions_terminal}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
