file(GLOB src_set_definitions
  "*.cpp"
)
add_library(ol_set_definitions OBJECT EXCLUDE_FROM_ALL
  ${src_set_definitions}
)
set(part_set_definitions
  $<TARGET_OBJECTS:ol_set_definitions>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
