file(GLOB src_type_abuse
  "*.cpp"
)
add_library(ol_type_abuse OBJECT EXCLUDE_FROM_ALL
  ${src_type_abuse}
)
set(part_type_abuse
  $<TARGET_OBJECTS:ol_type_abuse>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
