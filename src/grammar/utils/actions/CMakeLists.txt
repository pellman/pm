file(GLOB src_grammar_utils_actions
  "*.cpp"
)
add_library(ol_grammar_utils_actions OBJECT EXCLUDE_FROM_ALL
  ${src_grammar_utils_actions}
)
set(part_grammar_utils_actions
  $<TARGET_OBJECTS:ol_grammar_utils_actions>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
