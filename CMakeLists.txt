
cmake_minimum_required(VERSION 2.8)

###
# Basic Project Details

project(cppintrospection)

set(CPACK_PACKAGE_VERSION_MAJOR "3")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "2")

set(CPACK_PACKAGE_VERSION
	"${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")


find_package(Doxygen)
find_package(OpenGL)
find_package(OpenSceneGraph REQUIRED)

if(NOT OSG_SOURCE_DIR)
	get_filename_component(OSG_SOURCE_DIR "${OSG_INCLUDE_DIR}/.." ABSOLUTE)
	set(OSG_SOURCE_DIR "${OSG_SOURCE_DIR}" CACHE PATH "Path to the OpenSceneGraph source directory.")
endif()

add_definitions(-DCPPINTROSPECTION_CMAKE)
add_subdirectory(src)