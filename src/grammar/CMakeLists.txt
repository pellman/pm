add_subdirectory("actions")
add_subdirectory("syntax")

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
  ${part_grammar_actions}
  ${part_grammar_base}
  ${part_grammar_syntax}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
