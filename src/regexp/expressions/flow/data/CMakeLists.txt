file(GLOB src_regexp_expressions_flow_data
  "*.cpp"
)
add_library(ol_regexp_expressions_flow_data OBJECT EXCLUDE_FROM_ALL
  ${src_regexp_expressions_flow_data}
)
set(part_regexp_expressions_flow_data
  $<TARGET_OBJECTS:ol_regexp_expressions_flow_data>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
