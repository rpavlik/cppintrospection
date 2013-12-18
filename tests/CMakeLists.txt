include(BoostTestTargets)

include_directories(${OSG_INCLUDE_DIR} ${CPPINTROSPECTION_INCLUDE_DIRS})

add_boost_test(PointerToConst
	SOURCES
	PointerToConst.cpp
	DummyClasses.cpp
	DummyClasses.h
	LIBRARIES
	cppintrospection
)

add_boost_test(ValueConversion
	SOURCES
	ValueConversion.cpp
	DummyClasses.cpp
	DummyClasses.h
	LIBRARIES
	cppintrospection
)
