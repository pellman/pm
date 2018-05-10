file(GLOB src_dataset_syntax_functions
  "*.cpp"
)
add_library(ol_dataset_syntax_functions OBJECT EXCLUDE_FROM_ALL
  ${src_dataset_syntax_functions}
)
set(part_dataset_syntax_functions
  $<TARGET_OBJECTS:ol_dataset_syntax_functions>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
