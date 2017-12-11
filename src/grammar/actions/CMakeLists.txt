file(GLOB src_grammar_actions
  "*.cpp"
)
add_library(ol_grammar_actions OBJECT EXCLUDE_FROM_ALL
  ${src_grammar_actions}
)
set(part_grammar_actions
  $<TARGET_OBJECTS:ol_grammar_actions>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
