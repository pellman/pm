file(GLOB src_dataset_functions
  "*.cpp"
)
add_library(ol_dataset_functions OBJECT EXCLUDE_FROM_ALL
  ${src_dataset_functions}
)
set(part_dataset_functions
  $<TARGET_OBJECTS:ol_dataset_functions>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
