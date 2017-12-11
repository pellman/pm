add_subdirectory("functions")
add_subdirectory("syntax")

file(GLOB src_dataset_base
  "*.cpp"
)
add_library(ol_dataset_base OBJECT EXCLUDE_FROM_ALL
  ${src_dataset_base}
)
set(part_dataset_base
  $<TARGET_OBJECTS:ol_dataset_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
set(part_dataset
  ${part_dataset_base}
  ${part_dataset_functions}
  ${part_dataset_syntax}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
