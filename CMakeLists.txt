
cmake_minimum_required(VERSION 2.8)

###
# Basic Project Details

project(cppintrospection)

set(CPACK_PACKAGE_VERSION_MAJOR "3")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "2")

set(CPACK_PACKAGE_VERSION
	"${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

option(BUILD_GENWRAPPER "Build the wrapper generation tool?" ON)
option(BUILD_WRAPPERS "Build the wrappers for OpenSceneGraph?" OFF)

set(CPPINTROSPECTION_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
find_package(Doxygen)
find_package(OpenGL)
find_package(OpenSceneGraph REQUIRED)

if(NOT OSG_SOURCE_DIR)
	get_filename_component(OSG_SOURCE_DIR "${OSG_INCLUDE_DIR}/.." ABSOLUTE)
	set(OSG_SOURCE_DIR "${OSG_SOURCE_DIR}" CACHE PATH "Path to the OpenSceneGraph source directory.")
endif()

set(BIN_DIR bin)
set(INCLUDE_DIR include)
set(ARCH_DIR lib)
set(DATA_DIR share/cppintrospection)
if(WIN32)
	set(LIB_DIR bin)
	set(EXPORT_DIR cmake)
else()
	set(LIB_DIR lib)
	set(EXPORT_DIR ${LIB_DIR}/cppintrospection)
endif()

add_definitions(-DCPPINTROSPECTION_CMAKE)
add_subdirectory(src)
add_subdirectory(examples)

###
# Create config files to allow easy use of this library
###


# Set up use from build tree
configure_file(cppintrospection-config-build-tree.cmake.in cppintrospectionConfig.cmake @ONLY)
export(TARGETS cppintrospection
	NAMESPACE cppintrospection_imported_
	FILE cppintrospection-targets.cmake)
export(PACKAGE cppintrospection)

# Set up use from install tree
#install(EXPORT cppintrospection-sdk
#	DESTINATION ${EXPORT_DIR}
#	NAMESPACE cppintrospection_imported_
#	FILE cppintrospection-targets.cmake)
#configure_file(cppintrospection-config.cmake.in cppintrospection-config-for-install.cmake @ONLY)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/cppintrospection-config-for-install.cmake
#	RENAME cppintrospection-config.cmake
#	DESTINATION ${EXPORT_DIR})

