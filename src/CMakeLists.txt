configure_file(config.h.cmakein "${CMAKE_CURRENT_BINARY_DIR}/config.h")
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_subdirectory(cppintrospection)

if(BUILD_GENWRAPPER)
	add_subdirectory(genwrapper)
endif()

if(BUILD_WRAPPERS AND OSG_SOURCE_DIR AND EXISTS "${OSG_SOURCE_DIR}/include" AND DOXYGEN_FOUND)
	add_subdirectory(wrappers)
endif()
