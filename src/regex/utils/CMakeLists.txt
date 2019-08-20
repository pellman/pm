file(GLOB src_regex_utils
  "*.cpp"
)
add_library(ol_regex_utils OBJECT EXCLUDE_FROM_ALL
  ${src_regex_utils}
)
set(part_regex_utils
  $<TARGET_OBJECTS:ol_regex_utils>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
