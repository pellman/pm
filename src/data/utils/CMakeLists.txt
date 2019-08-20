file(GLOB src_data_utils
  "*.cpp"
)
add_library(ol_data_utils OBJECT EXCLUDE_FROM_ALL
  ${src_data_utils}
)
set(part_data_utils
  $<TARGET_OBJECTS:ol_data_utils>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
