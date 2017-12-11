file(GLOB src_dataset_syntax_functions_base
  "*.cpp"
)
add_library(ol_dataset_syntax_functions_base OBJECT EXCLUDE_FROM_ALL
  ${src_dataset_syntax_functions_base}
)
set(part_dataset_syntax_functions_base
  $<TARGET_OBJECTS:ol_dataset_syntax_functions_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
