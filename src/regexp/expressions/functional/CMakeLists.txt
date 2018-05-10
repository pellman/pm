file(GLOB src_regexp_expressions_functional
  "*.cpp"
)
add_library(ol_regexp_expressions_functional OBJECT EXCLUDE_FROM_ALL
  ${src_regexp_expressions_functional}
)
set(part_regexp_expressions_functional
  $<TARGET_OBJECTS:ol_regexp_expressions_functional>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
