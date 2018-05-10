file(GLOB src_regexp_expressions_flow_control
  "*.cpp"
)
add_library(ol_regexp_expressions_flow_control OBJECT EXCLUDE_FROM_ALL
  ${src_regexp_expressions_flow_control}
)
set(part_regexp_expressions_flow_control
  $<TARGET_OBJECTS:ol_regexp_expressions_flow_control>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
