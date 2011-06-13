configure_file(config.h.cmakein "${CMAKE_CURRENT_BINARY_DIR}/config.h")
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
add_subdirectory(genwrapper)
add_subdirectory(cppintrospection)