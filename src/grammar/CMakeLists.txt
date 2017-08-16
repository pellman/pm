add_library(grammar_ol OBJECT
  action.cpp
  context.cpp
  grammar.cpp
  node.cpp
  context/adataset.cpp
  syntax/action.cpp
  syntax/grammar.cpp
  syntax/interpreter.cpp
)
set(grammar_source_features
  cxx_auto_type
  cxx_range_for
)
set(grammar_header_features
  cxx_defaulted_functions
  cxx_generalized_initializers
  cxx_uniform_initialization
  cxx_nonstatic_member_init
  cxx_override
  cxx_right_angle_brackets
  cxx_rvalue_references
)
target_compile_features(grammar_ol PRIVATE
  ${grammar_source_features}
)
target_compile_features(grammar_ol PUBLIC
  ${grammar_header_features}
  ${type_abuse_features}
  ${utils_features}
)
