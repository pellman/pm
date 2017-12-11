add_subdirectory("actions")

file(GLOB src_grammar_syntax_base
  "*.cpp"
)
add_library(ol_grammar_syntax_base OBJECT EXCLUDE_FROM_ALL
  ${src_grammar_syntax_base}
)
set(part_grammar_syntax_base
  $<TARGET_OBJECTS:ol_grammar_syntax_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
set(part_grammar_syntax
  ${part_grammar_syntax_actions}
  ${part_grammar_syntax_base}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
