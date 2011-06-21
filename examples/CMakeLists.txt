find_package(OpenSceneGraph REQUIRED COMPONENTS osg osgDB)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include" ${OPENSCENEGRAPH_INCLUDE_DIRS})
add_subdirectory(simple_example)
add_subdirectory(detailed_list)
