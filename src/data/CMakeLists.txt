add_subdirectory("utils")

file(GLOB src_data_base
  "*.cpp"
)
add_library(ol_data_base OBJECT EXCLUDE_FROM_ALL
  ${src_data_base}
)
set(part_data_base
  $<TARGET_OBJECTS:ol_data_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
set(part_data
  ${part_data_base}
  ${part_data_utils}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
