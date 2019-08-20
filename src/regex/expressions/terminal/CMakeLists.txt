file(GLOB src_regex_expressions_terminal
  "*.cpp"
)
add_library(ol_regex_expressions_terminal OBJECT EXCLUDE_FROM_ALL
  ${src_regex_expressions_terminal}
)
set(part_regex_expressions_terminal
  $<TARGET_OBJECTS:ol_regex_expressions_terminal>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
