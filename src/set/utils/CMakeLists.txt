add_subdirectory("functions")

file(GLOB src_set_utils_base
  "*.cpp"
)
add_library(ol_set_utils_base OBJECT EXCLUDE_FROM_ALL
  ${src_set_utils_base}
)
set(part_set_utils_base
  $<TARGET_OBJECTS:ol_set_utils_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)

set(part_set_utils
  ${part_set_utils_base}
  ${part_set_utils_functions}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
