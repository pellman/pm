add_library(dataset_ol OBJECT
  function.cpp
  set.cpp
  functions/composition.cpp
  syntax/function.cpp
  syntax/interpreter.cpp
  syntax/set.cpp
)
set(dataset_source_features
  cxx_auto_type
  cxx_range_for
)
set(dataset_header_features
  cxx_defaulted_functions
  cxx_nonstatic_member_init
  cxx_override
  cxx_right_angle_brackets
  cxx_rvalue_references
)
target_compile_features(dataset_ol PRIVATE
  ${dataset_source_features}
)
target_compile_features(dataset_ol PUBLIC
  ${dataset_header_features}
  ${type_abuse_features}
  ${utils_features}
)
