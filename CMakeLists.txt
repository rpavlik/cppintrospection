
cmake_minimum_required(VERSION 2.8)

###
# Basic Project Details

project(cppintrospection)

find_package(Boost COMPONENTS filesystem regex thread REQUIRED)
find_package(Doxygen)
find_package(LibXml2 REQUIRED)
find_package(OpenGL)
find_package(OpenSceneGraph REQUIRED)

add_subdirectory(src)