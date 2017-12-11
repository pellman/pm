file(GLOB src_regexp_expressions_composition
  "*.cpp"
)
add_library(ol_regexp_expressions_composition OBJECT EXCLUDE_FROM_ALL
  ${src_regexp_expressions_composition}
)
set(part_regexp_expressions_composition
  $<TARGET_OBJECTS:ol_regexp_expressions_composition>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
