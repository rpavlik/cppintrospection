
cmake_minimum_required(VERSION 2.8)

###
# Basic Project Details

project(cppintrospection)

set(CPACK_PACKAGE_VERSION_MAJOR "3")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "2")

set(CPACK_PACKAGE_VERSION
	"${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

find_package(Boost COMPONENTS filesystem regex thread REQUIRED)
find_package(Doxygen)
find_package(LibXml2 REQUIRED)
find_package(OpenGL)
find_package(OpenSceneGraph REQUIRED)

add_definitions(-DCPPINTROSPECTION_CMAKE)
add_subdirectory(src)