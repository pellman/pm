add_subdirectory("control")
add_subdirectory("data")

set(part_regexp_expressions_flow
  ${part_regexp_expressions_flow_control}
  ${part_regexp_expressions_flow_data}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
