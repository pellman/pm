add_subdirectory("actions")

file(GLOB src_grammar_utils_base
  "*.cpp"
)
add_library(ol_grammar_utils_base OBJECT EXCLUDE_FROM_ALL
  ${src_grammar_utils_base}
)
set(part_grammar_utils_base
  $<TARGET_OBJECTS:ol_grammar_utils_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)

set(part_grammar_utils
  ${part_grammar_utils_base}
  ${part_grammar_utils_actions}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
