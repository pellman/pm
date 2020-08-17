file(GLOB src_devel_data
  "*.cpp"
)
add_library(ol_devel_data OBJECT EXCLUDE_FROM_ALL
  ${src_devel_data}
)
set(part_devel_data
  $<TARGET_OBJECTS:ol_devel_data>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
