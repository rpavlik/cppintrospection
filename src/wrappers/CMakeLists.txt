set(GENWRAPPER_CONF "${CMAKE_CURRENT_SOURCE_DIR}/../genwrapper/genwrapper.conf")

set(INPUT_DIR "${OSG_SOURCE_DIR}/")
set(HEADER_DIR "${OSG_SOURCE_DIR}/include")
set(OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/") # for doxygen
set(GENERATION_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

include_directories(${CPPINTROSPECTION_INCLUDE_DIRS})
# Extract files to exclude.
file(STRINGS "${GENWRAPPER_CONF}" IGNORED REGEX "ignore file .*")
string(REGEX MATCHALL "\"([^\"]*)\"" fns "${IGNORED}")
string(REPLACE "\"" "" IGNORED_FILES "${fns}")
message(STATUS "Ignored files: ${IGNORED_FILES}")

function(add_wrapper _module)
	set(LIBRARIES ${ARGN})
	file(GLOB_RECURSE infiles RELATIVE "${HEADER_DIR}" "${HEADER_DIR}/${_module}/*")
	list(REMOVE_ITEM infiles ${IGNORED_FILES})
	set(SOURCES)
	foreach(infile ${infiles})
		set(outfile "${GENERATION_DIR}/src/osgWrappers/introspection/${infile}.cpp")
		set_property(SOURCE "${outfile}" PROPERTY GENERATED true)
		list(APPEND SOURCES "${outfile}")		
	endforeach()
	add_library(osgwrapper_${_module} MODULE ${SOURCES})
	target_link_libraries(osgwrapper_${_module} ${LIBRARIES})
endfunction()

add_wrapper(osg ${OSG_LIBRARIES})

configure_file(Doxyfile.in "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/xml"
	COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
	COMMENT "Parsing header files with Doxygen"
	VERBATIM)
add_custom_target(generate_wrappers
	COMMAND genwrapper -c "${GENWRAPPER_CONF}" "${CMAKE_CURRENT_BINARY_DIR}" "${GENERATION_DIR}"
	DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/xml" "${GENWRAPPER_CONF}")

