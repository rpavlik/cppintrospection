/**
        @file
        @brief Implementation

        @date 2013

        @author
        Ryan Pavlik
        <rpavlik@iastate.edu> and <abiryan@ryand.net>
        http://academic.cleardefinition.com/
        Iowa State University Virtual Reality Applications Center
        Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE Value - type conversion tests

#include <BoostTestTargetConfig.h>

#include <boost/test/unit_test_monitor.hpp>

#include "DummyClasses.h"

#include <cppintrospection/Reflection>
#include <cppintrospection/Value>
#include <cppintrospection/Type>
#include <cppintrospection/variant_cast>

namespace intro = cppintrospection;

void translate_cppintrospection_exceptions(const cppintrospection::Exception &e)
{
    BOOST_ERROR(e.what());
}

class Fixture
{
public:
    Fixture()
    {
        ensureRegistered();
        boost::unit_test::unit_test_monitor.register_exception_translator
            <intro::Exception>(&translate_cppintrospection_exceptions);
        acceptType = &intro::Reflection::getType("Acceptor");
    }
    intro::Type const *acceptType;

    Acceptor a;
    ValueSrc src;
    ValueDest dest;

private:
};

inline intro::ValueList createValueList(intro::Value v)
{
    return intro::ValueList(1, v);
}

BOOST_AUTO_TEST_CASE(ValueDestToValueDest)
{
    Fixture f;
    BOOST_CHECK(f.acceptType->getCompatibleMethod(
        "acceptValueDest", createValueList(f.dest), true));

    intro::ValueList vl;
    BOOST_CHECK_NO_THROW(
        (vl = createValueList(f.dest),
         f.acceptType->invokeMethod("acceptValueDest", &f.a, vl, true)));
}

BOOST_AUTO_TEST_CASE(ValueDestToValueDestRefConst)
{
    Fixture f;
    BOOST_CHECK(f.acceptType->getCompatibleMethod(
        "acceptValueDestRefConst", createValueList(f.dest), true));

    intro::ValueList vl;
    BOOST_CHECK_NO_THROW((
        vl = createValueList(f.dest),
        f.acceptType->invokeMethod("acceptValueDestRefConst", &f.a, vl, true)));
}

BOOST_AUTO_TEST_CASE(ValueSrcToValueDest)
{
    Fixture f;
    BOOST_CHECK(f.acceptType->getCompatibleMethod(
        "acceptValueDest", createValueList(f.src), true));

    intro::ValueList vl;
    BOOST_CHECK_NO_THROW(
        (vl = createValueList(f.src),
         f.acceptType->invokeMethod("acceptValueDest", &f.a, vl, true)));
}

BOOST_AUTO_TEST_CASE(ValueSrcToValueDestRefConst)
{
    Fixture f;
    BOOST_CHECK(f.acceptType->getCompatibleMethod(
        "acceptValueDestRefConst", createValueList(f.src), true));

    intro::ValueList vl;
    BOOST_CHECK_NO_THROW((
        vl = createValueList(f.src),
        f.acceptType->invokeMethod("acceptValueDestRefConst", &f.a, vl, true)));
}
