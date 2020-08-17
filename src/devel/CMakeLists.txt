add_subdirectory("char_set")
add_subdirectory("data")
add_subdirectory("par_system")
add_subdirectory("parser")
add_subdirectory("stream")

set(part_devel
  ${part_devel_char_set}
  ${part_devel_data}
  ${part_devel_par_system}
  ${part_devel_parser}
  ${part_devel_stream}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
