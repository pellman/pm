add_subdirectory("string")
add_subdirectory("symbol")

file(GLOB src_regexp_expressions_terminal_base
  "*.cpp"
)
add_library(ol_regexp_expressions_terminal_base OBJECT EXCLUDE_FROM_ALL
  ${src_regexp_expressions_terminal_base}
)
set(part_regexp_expressions_terminal_base
  $<TARGET_OBJECTS:ol_regexp_expressions_terminal_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
set(part_regexp_expressions_terminal
  ${part_regexp_expressions_terminal_base}
  ${part_regexp_expressions_terminal_string}
  ${part_regexp_expressions_terminal_symbol}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
