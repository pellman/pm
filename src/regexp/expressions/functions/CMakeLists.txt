file(GLOB src_regexp_expressions_functions
  "*.cpp"
)
add_library(ol_regexp_expressions_functions OBJECT EXCLUDE_FROM_ALL
  ${src_regexp_expressions_functions}
)
set(part_regexp_expressions_functions
  $<TARGET_OBJECTS:ol_regexp_expressions_functions>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
