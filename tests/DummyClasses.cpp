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

// Internal Includes
#include "DummyClasses.h"

// Library/third-party includes
// - none up here

// Standard includes
// - none

Parent::~Parent()
{
}

Child::~Child()
{
}

#include <cppintrospection/ReflectionMacros>
#include <cppintrospection/TypedMethodInfo>

// Must undefine IN and OUT macros defined in Windows headers
#ifdef IN
#undef IN
#endif
#ifdef OUT
#undef OUT
#endif

BEGIN_OBJECT_REFLECTOR(Parent)
I_DeclaringFile("DummyClasses.h");
I_Constructor0(____Parent, "", "");
I_Method0(const char *, identify, Properties::VIRTUAL, __C5_char_P1__identify,
          "Return the object identity.",
          "Must be overridden by derived classes. ");
END_REFLECTOR

BEGIN_OBJECT_REFLECTOR(Child)
I_DeclaringFile("DummyClasses.h");
I_BaseType(Parent);
I_Constructor0(____Child, "", "");
I_Method0(const char *, identify, Properties::VIRTUAL, __C5_char_P1__identify,
          "Returns the name of this class.", "");
END_REFLECTOR

BEGIN_VALUE_REFLECTOR(ValueSrc)
I_DeclaringFile("DummyClasses.h");
I_Constructor0(____ValueSrc, "", "");
END_REFLECTOR

BEGIN_VALUE_REFLECTOR(ValueDest)
I_DeclaringFile("DummyClasses.h");
I_Constructor0(____ValueDest, "", "");
I_Constructor1(IN, const ValueSrc &, other, Properties::NON_EXPLICIT,
               ____ValueDest__C5_ValueSrc_R1, "", "");
END_REFLECTOR

BEGIN_OBJECT_REFLECTOR(Acceptor)
I_DeclaringFile("DummyClasses.h");
I_Constructor0(____Acceptor, "", "");
I_Method1(void, acceptParentPtr, IN, Parent *, p, Properties::NON_VIRTUAL,
          __void__acceptParentPtr__Parent_P1, "", "");

I_Method1(void, acceptParentPtrConst, IN, const Parent *, p,
          Properties::NON_VIRTUAL, __void__acceptParentPtrConst__C5_Parent_P1,
          "", "");
I_Method1(void, acceptParentRef, IN, Parent &, p, Properties::NON_VIRTUAL,
          __void__acceptParentRef__Parent_R1, "", "");
I_Method1(void, acceptParentRefConst, IN, const Parent &, p,
          Properties::NON_VIRTUAL, __void__acceptParentRefConst__C5_Parent_R1,
          "", "");
I_Method1(void, acceptValueDest, IN, ValueDest, v, Properties::NON_VIRTUAL,
          __void__acceptValueDest__ValueDest, "", "");
I_Method1(void, acceptValueDestRefConst, IN, const ValueDest &, v,
          Properties::NON_VIRTUAL,
          __void__acceptValueDestRefConst__C5_ValueDest_R1, "", "");
END_REFLECTOR

void ensureRegistered()
{
    // This is a dummy function to make sure this object file is linked
    // in and the static members are initialized when we need them.
}
