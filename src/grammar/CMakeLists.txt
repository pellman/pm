add_subdirectory("definitions")
add_subdirectory("utils")

file(GLOB src_grammar_base
  "*.cpp"
)
add_library(ol_grammar_base OBJECT EXCLUDE_FROM_ALL
  ${src_grammar_base}
)
set(part_grammar_base
  $<TARGET_OBJECTS:ol_grammar_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)

set(part_grammar
  ${part_grammar_base}
  ${part_grammar_definitions}
  ${part_grammar_utils}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
