set(GENWRAPPER_CONF "${CMAKE_CURRENT_SOURCE_DIR}/../genwrapper/genwrapper.conf")

set(INPUT_DIR "${OSG_SOURCE_DIR}/")
set(HEADER_DIR "${OSG_SOURCE_DIR}/include")
set(OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/") # for doxygen
set(GENERATION_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

include_directories(${CPPINTROSPECTION_INCLUDE_DIRS})

# Extract files to exclude.
# This line forces a re-CMake when the genwrapper.conf file changes.
configure_file("${GENWRAPPER_CONF}" "${CMAKE_CURRENT_BINARY_DIR}/genwrapper.conf")
file(STRINGS "${CMAKE_CURRENT_BINARY_DIR}/genwrapper.conf" IGNORED REGEX "ignore file .*")
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
	add_dependencies(osgwrapper_${_module} generate_wrappers)

	set_property(DIRECTORY APPEND PROPERTY GENWRAPPER_OUTPUTS ${SOURCES})

	set_property(TARGET osgwrapper_${_module} PROPERTY PREFIX "")
endfunction()

function(generate_wrapper_sources)
	configure_file(Doxyfile.in "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
	add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/xml" "${CMAKE_CURRENT_BINARY_DIR}/xml/index.xml"
		COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
		COMMENT "Parsing header files with Doxygen"
		DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
		VERBATIM)

	get_property(OUTPUTS DIRECTORY PROPERTY GENWRAPPER_OUTPUTS)

	add_custom_command(OUTPUT "${GENERATION_DIR}" "${GENERATION_DIR}/generate.stamp" #${OUTPUTS}
		COMMAND genwrapper -c "${GENWRAPPER_CONF}" "${CMAKE_CURRENT_BINARY_DIR}" "${GENERATION_DIR}"
		COMMAND touch "${GENERATION_DIR}/generate.stamp"
		COMMENT "Generating wrapper sources"
		DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/xml" "${CMAKE_CURRENT_BINARY_DIR}/xml/index.xml" "${GENWRAPPER_CONF}"
		VERBATIM)
	add_custom_target(generate_wrappers
		DEPENDS "${GENERATION_DIR}/generate.stamp")
endfunction()


include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})
find_package(OpenSceneGraph COMPONENTS
	OpenThreads
	osgAnimation
	osg
	osgDB
	osgFX
	osgGA
	osgManipulator
	osgParticle
	osgShadow
	osgSim
	osgTerrain
	osgText
	osgUtil
	osgViewer
	osgVolume
	osgWidget)


add_wrapper(OpenThreads ${OPENTHREADS_LIBRARIES})
add_wrapper(osgAnimation ${OSGANIMATION_LIBRARIES})
add_wrapper(osg ${OSG_LIBRARIES})
add_wrapper(osgDB ${OSGDB_LIBRARIES})
add_wrapper(osgFX ${OSGFX_LIBRARIES})
add_wrapper(osgGA ${OSGGA_LIBRARIES})
add_wrapper(osgManipulator ${OSGMANIPULATOR_LIBRARIES})
add_wrapper(osgParticle ${OSGPARTICLE_LIBRARIES})
add_wrapper(osgShadow ${OSGSHADOW_LIBRARIES})
add_wrapper(osgSim ${OSGSIM_LIBRARIES})
add_wrapper(osgTerrain ${OSGTERRAIN_LIBRARIES})
add_wrapper(osgText ${OSGTEXT_LIBRARIES})
add_wrapper(osgUtil ${OSGUTIL_LIBRARIES})
add_wrapper(osgViewer ${OSGVIEWER_LIBRARIES})
add_wrapper(osgVolume ${OSGVOLUME_LIBRARIES})
add_wrapper(osgWidget ${OSGWIDGET_LIBRARIES})


generate_wrapper_sources()
