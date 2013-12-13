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

#define BOOST_TEST_MODULE Const pointer conversion tests

#include <BoostTestTargetConfig.h>

#include <boost/test/unit_test_monitor.hpp>

#include "DummyClasses.h"

#include <cppintrospection/Reflection>
#include <cppintrospection/Value>
#include <cppintrospection/Type>
#include <cppintrospection/variant_cast>

namespace intro = cppintrospection;

void translate_cppintrospection_exceptions(cppintrospection::Exception &e)
{
    BOOST_ERROR(e.what());
}

template <typename T> struct dereferenceIfRequested
{
    static T apply(T v)
    {
        return v;
    }
};

template <typename T> struct dereferenceIfRequested<T &>
{
    static T &apply(T *v)
    {
        return *v;
    }
};

class Fixture
{
public:
    Fixture()
        : p_ptr(&p)
        , c_ptr(&c)
    {
        ensureRegistered();
        boost::unit_test::unit_test_monitor.register_exception_translator
            <intro::Exception &>(&translate_cppintrospection_exceptions);
        acceptType = &intro::Reflection::getType("Acceptor");
    }
    template <typename T> T getParentAs()
    {
        return dereferenceIfRequested<T>::apply(p_ptr);
    }

    template <typename T> T getChildAs()
    {
        return dereferenceIfRequested<T>::apply(c_ptr);
    }

    const intro::Type *acceptType;

private:
    Parent p;
    Parent *p_ptr;
    Child c;
    Child *c_ptr;
};

inline intro::ValueList createValueList(intro::Value v)
{
    return intro::ValueList(1, v);
}

#if 0
namespace cppintrospection {
    std::ostream &operator<<(std::ostream &os, Exception const &e) {
        os << "cppintrospection::Exception: " << e.what();
        return os;
    }
}

template <typename Src, typename Dest, typename Input>
void testVariantCast(Input input) {
    BOOST_MESSAGE(("Variant cast of underlying "
                  + typeof<Input>().getQualifiedName() + "from "
                  + typeof<Src>().getQualifiedName() + " to "
                  + typeof<Dest>().getQualifiedName()));
    BOOST_CHECK_NO_THROW(intro::variant_cast<Dest>(static_cast<Src>(input)));
}

#endif

BOOST_AUTO_TEST_CASE(ParentPtrToParentPtr)
{
    Fixture f;
    BOOST_CHECK(intro::variant_cast<Parent *>(f.getParentAs<Parent *>()));

    BOOST_CHECK(f.acceptType->getCompatibleMethod(
        "acceptParentPtr", createValueList(f.getParentAs<Parent *>()), true));
}

BOOST_AUTO_TEST_CASE(ConstParentPtrToConstParentPtr)
{
    Fixture f;
    BOOST_CHECK(intro::variant_cast
                <const Parent *>(f.getParentAs<const Parent *>()));

    BOOST_CHECK(f.acceptType->getCompatibleMethod(
        "acceptParentPtrConst",
        createValueList(f.getParentAs<const Parent *>()), true));
}

BOOST_AUTO_TEST_CASE(ParentPtrToConstParentPtr)
{
    Fixture f;
    BOOST_CHECK(intro::variant_cast<const Parent *>(f.getParentAs<Parent *>()));

    BOOST_CHECK(f.acceptType->getCompatibleMethod(
        "acceptParentPtrConst", createValueList(f.getParentAs<Parent *>()),
        true));
}

BOOST_AUTO_TEST_CASE(ChildPtrToParentPtr)
{
    Fixture f;
    BOOST_CHECK(intro::variant_cast<Parent *>(f.getChildAs<Child *>()));

    BOOST_CHECK(f.acceptType->getCompatibleMethod(
        "acceptParentPtr", createValueList(f.getChildAs<Child *>()), true));
}

BOOST_AUTO_TEST_CASE(ConstChildPtrToConstParentPtr)
{
    Fixture f;
    BOOST_CHECK(intro::variant_cast
                <const Parent *>(f.getChildAs<const Child *>()));

    BOOST_CHECK(f.acceptType->getCompatibleMethod(
        "acceptParentPtrConst", createValueList(f.getChildAs<const Child *>()),
        true));
}

BOOST_AUTO_TEST_CASE(ParentPtrToParentRef)
{
    Fixture f;
    BOOST_CHECK_NO_THROW(intro::variant_cast
                         <Parent &>(f.getParentAs<Parent *>()));

    BOOST_CHECK(f.acceptType->getCompatibleMethod(
        "acceptParentRef", createValueList(f.getParentAs<Parent *>()), true));
}
