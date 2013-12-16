set(SOURCES
	ConstructorInfo.cpp
	Converter.cpp
	CustomAttribute.cpp
	CustomAttributeProvider.cpp
	DefaultReflectors.cpp
	GenericReflectorBase.cpp
	MethodInfo.cpp
	PropertyInfo.cpp
	Reflection.cpp
	Reflector.cpp
	Type.cpp
	Utility.cpp
	Value.cpp
	Version.cpp)

set(HEADERS
	../../include/cppintrospection/Attributes
	../../include/cppintrospection/Comparator
	../../include/cppintrospection/ConstructorInfo
	../../include/cppintrospection/Converter
	../../include/cppintrospection/ConverterProxy
	../../include/cppintrospection/CustomAttribute
	../../include/cppintrospection/CustomAttributeProvider
	../../include/cppintrospection/Exceptions
	../../include/cppintrospection/Export
	../../include/cppintrospection/ExtendedTypeInfo
	../../include/cppintrospection/GenericReflectorBase
	../../include/cppintrospection/InstanceCreator
	../../include/cppintrospection/MethodInfo
	../../include/cppintrospection/ParameterInfo
	../../include/cppintrospection/PropertyInfo
	../../include/cppintrospection/PublicMemberAccessor
	../../include/cppintrospection/ReaderWriter
	../../include/cppintrospection/Reflection
	../../include/cppintrospection/ReflectionMacros
	../../include/cppintrospection/Reflector
	../../include/cppintrospection/StaticMethodInfo
	../../include/cppintrospection/Type
	../../include/cppintrospection/TypeNameAliasProxy
	../../include/cppintrospection/TypedConstructorInfo
	../../include/cppintrospection/TypedMethodInfo
	../../include/cppintrospection/Utility
	../../include/cppintrospection/Value
	../../include/cppintrospection/Version
	../../include/cppintrospection/type_traits
	../../include/cppintrospection/variant_cast
	../../include/cppintrospection/variant_cast_fwd)

add_definitions(-DCPPINTROSPECTION_LIBRARY)
include_directories(../../include ${OPENSCENEGRAPH_INCLUDE_DIRS})
add_library(cppintrospection SHARED ${SOURCES} ${HEADERS})
target_link_libraries(cppintrospection ${OPENSCENEGRAPH_LIBRARIES})


install(TARGETS cppintrospection
	EXPORT cppintrospection-sdk
	RUNTIME DESTINATION ${BIN_DIR} COMPONENT runtime
	LIBRARY DESTINATION ${LIB_DIR} COMPONENT sdk
	ARCHIVE DESTINATION ${ARCH_DIR} COMPONENT sdk
	PUBLIC_HEADER DESTINATION ${INCLUDE_DIR}/cppintrospection COMPONENT sdk)
