add_subdirectory("base")

file(GLOB src_grammar_syntax_actions_special
  "*.cpp"
)
add_library(ol_grammar_syntax_actions_special OBJECT EXCLUDE_FROM_ALL
  ${src_grammar_syntax_actions_special}
)
set(part_grammar_syntax_actions_special
  $<TARGET_OBJECTS:ol_grammar_syntax_actions_special>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
set(part_grammar_syntax_actions
  ${part_grammar_syntax_actions_base}
  ${part_grammar_syntax_actions_special}
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
