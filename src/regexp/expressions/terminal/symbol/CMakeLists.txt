file(GLOB src_regexp_expressions_terminal_symbol
  "*.cpp"
)
add_library(ol_regexp_expressions_terminal_symbol OBJECT EXCLUDE_FROM_ALL
  ${src_regexp_expressions_terminal_symbol}
)
set(part_regexp_expressions_terminal_symbol
  $<TARGET_OBJECTS:ol_regexp_expressions_terminal_symbol>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
