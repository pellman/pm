add_subdirectory("creation")
add_subdirectory("devel")

file(GLOB src_base
  "*.cpp"
)
add_library(ol_base OBJECT EXCLUDE_FROM_ALL
  ${src_base}
)
set(part_base
  $<TARGET_OBJECTS:ol_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
set(all_parts
  ${part_base}
  ${part_creation}
  ${part_devel}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
