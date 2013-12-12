/** @file
	@brief Header

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

#ifndef INCLUDED_DummyClasses_h_GUID_f9ff7fd4_7eee_4f9d_a95f_dcbd31f7f515
#define INCLUDED_DummyClasses_h_GUID_f9ff7fd4_7eee_4f9d_a95f_dcbd31f7f515

// Internal Includes
// - none

// Library/third-party includes
// - none

// Standard includes
// - none

class Parent {
    public:
        Parent() {}
        virtual ~Parent();
        
        virtual const char * identify() const { return "Parent"; }
};

class Child : public Parent {
    public:
        Child() {}
        virtual ~Child();
        
        virtual const char * identify() const { return "Child"; }
};

class Acceptor {
    public:
        Acceptor() {};
        
        void acceptParentPtr(Parent * p) {}
        void acceptParentPtrConst(const Parent * p) {}
        void acceptParentRef(Parent & p) {}
        void acceptParentRefConst(const Parent & p) {}
};

void ensureRegistered();

#endif // INCLUDED_DummyClasses_h_GUID_f9ff7fd4_7eee_4f9d_a95f_dcbd31f7f515
