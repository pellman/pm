add_library(type_abuse INTERFACE)
set(type_abuse_features
  cxx_default_function_template_args
  cxx_defaulted_functions
  cxx_delegating_constructors
  cxx_nullptr
  cxx_override
  cxx_right_angle_brackets
  cxx_rvalue_references
  cxx_variadic_templates
  PARENT_SCOPE
)
target_compile_features(type_abuse INTERFACE ${type_abuse_features})
