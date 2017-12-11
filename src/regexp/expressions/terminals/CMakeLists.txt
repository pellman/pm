file(GLOB src_regexp_expressions_terminals
  "*.cpp"
)
add_library(ol_regexp_expressions_terminals OBJECT EXCLUDE_FROM_ALL
  ${src_regexp_expressions_terminals}
)
set(part_regexp_expressions_terminals
  $<TARGET_OBJECTS:ol_regexp_expressions_terminals>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
