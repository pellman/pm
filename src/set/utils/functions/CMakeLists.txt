file(GLOB src_set_utils_functions
  "*.cpp"
)
add_library(ol_set_utils_functions OBJECT EXCLUDE_FROM_ALL
  ${src_set_utils_functions}
)
set(part_set_utils_functions
  $<TARGET_OBJECTS:ol_set_utils_functions>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
