file(GLOB src_grammar_syntax_actions
  "*.cpp"
)
add_library(ol_grammar_syntax_actions OBJECT EXCLUDE_FROM_ALL
  ${src_grammar_syntax_actions}
)
set(part_grammar_syntax_actions
  $<TARGET_OBJECTS:ol_grammar_syntax_actions>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
