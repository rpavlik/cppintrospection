find_package(Boost COMPONENTS filesystem regex REQUIRED)
add_definitions(-DBOOST_ALL_DYN_LINK)

find_package(LibXml2 REQUIRED)

include_directories(${LIBXML2_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
set(SOURCES
	Configuration.cpp
	Configuration.h
	FileSystemUtils.cpp
	FileSystemUtils.h
	NodeMap.cpp
	NodeMap.h
	Notify.cpp
	Notify.h
	PathNameUtils.cpp
	PathNameUtils.h
	RegistryBuilder.cpp
	RegistryBuilder.h
	TypeDesc.cpp
	TypeDesc.h
	TypeNameUtils.cpp
	TypeNameUtils.h
	TypeRegistry.cpp
	TypeRegistry.h
	WrapperGenerator.cpp
	WrapperGenerator.h
	XML_node.h
	XML_parser.h
	main.cpp)

add_executable(genwrapper ${SOURCES})
target_link_libraries(genwrapper ${Boost_FILESYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY} ${LIBXML2_LIBRARIES})