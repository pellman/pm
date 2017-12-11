file(GLOB src_grammar_syntax_actions_base
  "*.cpp"
)
add_library(ol_grammar_syntax_actions_base OBJECT EXCLUDE_FROM_ALL
  ${src_grammar_syntax_actions_base}
)
set(part_grammar_syntax_actions_base
  $<TARGET_OBJECTS:ol_grammar_syntax_actions_base>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
