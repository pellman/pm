file(GLOB src_regexp_expressions_terminal_string
  "*.cpp"
)
add_library(ol_regexp_expressions_terminal_string OBJECT EXCLUDE_FROM_ALL
  ${src_regexp_expressions_terminal_string}
)
set(part_regexp_expressions_terminal_string
  $<TARGET_OBJECTS:ol_regexp_expressions_terminal_string>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
