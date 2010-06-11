cmake_minimum_required(VERSION 2.6)

PROJECT(genwrapper)

FIND_PACKAGE(Boost COMPONENTS regex)
FIND_PACKAGE(LibXml2)

SET(SOURCES
    Configuration.cpp
    FileSystemUtils.cpp
    main.cpp
    NodeMap.cpp
    Notify.cpp
    PathNameUtils.cpp
    RegistryBuilder.cpp
    TypeDesc.cpp
    TypeNameUtils.cpp
    TypeRegistry.cpp
    WrapperGenerator.cpp
)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR} ${LIBXML2_INCLUDE_DIR})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

ADD_EXECUTABLE(genwrapper ${SOURCES})

TARGET_LINK_LIBRARIES(genwrapper ${LIBXML2_LIBRARIES} ${Boost_REGEX_LIBRARY})
