configure_file(config.h.cmakein "${CMAKE_CURRENT_BINARY_DIR}/config.h")
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
add_subdirectory(genwrapper)
add_subdirectory(cppintrospection)

if(OSG_SOURCE_DIR AND EXISTS "${OSG_SOURCE_DIR}/include" AND DOXYGEN_FOUND)
	set(INPUT_DIR "${OSG_SOURCE_DIR}/")
	set(OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/")
	configure_file(Doxyfile.in "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
	add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/xml"
		COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
		COMMENT "Parsing header files with Doxygen"
		VERBATIM)
	add_custom_target(generate_wrappers
		COMMAND genwrapper -c "${CMAKE_CURRENT_SOURCE_DIR}/genwrapper/genwrapper.conf" "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}/generated"
		DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/xml")
endif()