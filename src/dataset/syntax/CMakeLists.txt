add_subdirectory("functions")

set(part_dataset_syntax
  ${part_dataset_syntax_functions}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
