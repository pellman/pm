file(GLOB src_regex_expressions_flow
  "*.cpp"
)
add_library(ol_regex_expressions_flow OBJECT EXCLUDE_FROM_ALL
  ${src_regex_expressions_flow}
)
set(part_regex_expressions_flow
  $<TARGET_OBJECTS:ol_regex_expressions_flow>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
