add_library(utils INTERFACE)
set(utils_features
  cxx_auto_type
  cxx_range_for
  cxx_rvalue_references
  cxx_unrestricted_unions
  PARENT_SCOPE
)
target_compile_features(utils INTERFACE ${utils_features})
