file(GLOB src_devel_par_system
  "*.cpp"
)
add_library(ol_devel_par_system OBJECT EXCLUDE_FROM_ALL
  ${src_devel_par_system}
)
set(part_devel_par_system
  $<TARGET_OBJECTS:ol_devel_par_system>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
