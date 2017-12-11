add_subdirectory("base")

file(GLOB src_dataset_syntax_functions_special
  "*.cpp"
)
add_library(ol_dataset_syntax_functions_special OBJECT EXCLUDE_FROM_ALL
  ${src_dataset_syntax_functions_special}
)
set(part_dataset_syntax_functions_special
  $<TARGET_OBJECTS:ol_dataset_syntax_functions_special>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
set(part_dataset_syntax_functions
  ${part_dataset_syntax_functions_base}
  ${part_dataset_syntax_functions_special}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
