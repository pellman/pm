add_subdirectory("definitions")
add_subdirectory("utils")

file(GLOB src_set_base
  "*.cpp"
)
add_library(ol_set_base OBJECT EXCLUDE_FROM_ALL
  ${src_set_base}
)
set(part_set_base
  $<TARGET_OBJECTS:ol_set_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
set(part_set
  ${part_set_base}
  ${part_set_definitions}
  ${part_set_utils}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
