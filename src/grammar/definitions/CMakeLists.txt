file(GLOB src_grammar_definitions
  "*.cpp"
)
add_library(ol_grammar_definitions OBJECT EXCLUDE_FROM_ALL
  ${src_grammar_definitions}
)
set(part_grammar_definitions
  $<TARGET_OBJECTS:ol_grammar_definitions>
  CACHE INTERNAL "КОСТЫЛЬ, нельзя так просто заалиасить объектную библиотеку"
)
