generate_idl_cpp(echo ${CMAKE_SOURCE_DIR}/tests)

add_unit_test(echo "echo.cc;${ALL_IDL_CPP_STUBS}")

add_custom_target(generate_idl_cpp DEPENDS ${ALL_IDL_CPP_STUBS})
add_dependencies(echo generate_idl_cpp)

target_link_libraries(echo ${PROJECT_NAME})
target_compile_options(echo PRIVATE "-Wno-unused-variable")
pkg_config_use_dependency(echo omniORB4)
