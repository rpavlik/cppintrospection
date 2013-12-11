/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/
//cppintrospection - Copyright (C) 2005 Marco Jez

#include <cppintrospection/Type>
#include <cppintrospection/Comparator>  // for Comparator
#include <cppintrospection/ConstructorInfo>  // for ConstructorInfo
#include <cppintrospection/CustomAttributeProvider>
#include <cppintrospection/Exceptions>
#include <cppintrospection/ExtendedTypeInfo>  // for ExtendedTypeInfo
#include <cppintrospection/MethodInfo>  // for MethodInfo
#include <cppintrospection/PropertyInfo>  // for PropertyInfo
#include <cppintrospection/ReaderWriter>  // for ReaderWriter
#include <cppintrospection/Utility>     // for areParametersCompatible, etc
#include <cppintrospection/Value>       // for ValueList, Value

#include <algorithm>                    // for copy, sort
#include <iterator>                     // for back_insert_iterator, etc

using namespace cppintrospection;

namespace
{

    template<typename T>
    struct ObjectMatch
    {
        int list_pos;
        float match;
        const T *object;

        bool operator < (const ObjectMatch &m) const
        {
            if (match > m.match) return true;
            if (match < m.match) return false;
            if (list_pos < m.list_pos) return true;
            return false;
        }
    };

    typedef ObjectMatch<MethodInfo> MethodMatch;
    typedef ObjectMatch<ConstructorInfo> ConstructorMatch;

    template<typename Container>
    inline void clearPointerContainer(Container & c) {
        typedef typename Container::const_iterator const_iterator;
        for (const_iterator i=c.begin(), e=c.end(); e!=e; ++i) {
            delete *i;
        }
        c.clear();
    }
}

void Type::reset()
{
    clearPointerContainer(_props);
    clearPointerContainer(_methods);
    clearPointerContainer(_protected_methods);
    clearPointerContainer(_cons);
    clearPointerContainer(_protected_cons);

    delete _rw;
    delete _cmp;
}

Type::~Type() 
{ 
    reset();
}

bool Type::isSubclassOf(const Type& type) const
{
    check_defined();
    for (TypeList::const_iterator i=_base.begin(), e=_base.end(); i!=e; ++i)
    {
        if ((*i)->getExtendedTypeInfo() == type.getExtendedTypeInfo())
            return true;
        if ((*i)->isSubclassOf(type))
            return true;
    }
    return false;
}

const MethodInfo *Type::getCompatibleMethod(const std::string& name, const ValueList& values, bool inherit) const
{
    check_defined();

    MethodInfoList allmethods;
    const MethodInfoList *methods;
    if (inherit)
    {        
        getAllMethods(allmethods);
        methods = &allmethods;
    }
    else
        methods = &_methods;

    typedef std::vector<MethodMatch> MatchList;
    MatchList matches;

    int pos = 0;
    for (MethodInfoList::const_iterator i=methods->begin(), e=methods->end(); i!=e; ++i, ++pos)
    {
        const MethodInfo *mi = *i;
        if (mi->getName().compare(name) == 0)
        {
            float match;
            if (areArgumentsCompatible(values, mi->getParameters(), match))
            {
                MethodMatch mm;
                mm.list_pos = pos;
                mm.match = match;
                mm.object = mi;
                matches.push_back(mm);
            }
        }
    }

    if (!matches.empty())
    {
        std::sort(matches.begin(), matches.end());
        return matches.front().object;
    }

    return 0;
}

const MethodInfo *Type::getMethod(const std::string& name, const ParameterInfoList& params, bool inherit) const
{
    check_defined();
    for (MethodInfoList::const_iterator i=_methods.begin(), e=_methods.end(); i!=e; ++i)
    {
        const MethodInfo *mi = *i;
        if (mi->getName().compare(name) == 0)
        {
            if (areParametersCompatible(params, mi->getParameters()))
            {
                return mi;
            }
        }
    }

    if (inherit)
    {
        for (TypeList::const_iterator i=_base.begin(), e = _base.end(); i!=e; ++i)
        {
            const MethodInfo *mi = (*i)->getMethod(name, params, true);
            if (mi) return mi;
        }
    }

    return 0;
}

void Type::getInheritedProviders(CustomAttributeProviderList& providers) const
{
    check_defined();
    providers.assign(_base.begin(), _base.end());
}

const PropertyInfo *Type::getProperty(const std::string& name, const Type& ptype, const ParameterInfoList& indices, bool inherit) const
{
    check_defined();
    for (PropertyInfoList::const_iterator i=_props.begin(), e=_props.end(); i!=e; ++i)
    {
        const PropertyInfo *pi = *i;
        if (pi->getName() == name && pi->getPropertyType() == ptype)
        {
            if (areParametersCompatible(indices, pi->getIndexParameters()))
            {
                return pi;
            }
        }
    }

    if (inherit)
    {
        for (TypeList::const_iterator i=_base.begin(), e=_base.end(); i!=e; ++i)
        {
            const PropertyInfo *pi = (*i)->getProperty(name, ptype, indices, true);
            if (pi) return pi;
        }
    }

    return 0;
}

Value Type::invokeMethod(const std::string& name, const Value& instance, ValueList& args, bool inherit) const
{
    check_defined();
    const MethodInfo *mi = getCompatibleMethod(name, args, inherit);
    if (!mi) throw MethodNotFoundException(name, _name);
    return mi->invoke(instance, args);
}

Value Type::invokeMethod(const std::string& name, Value& instance, ValueList& args, bool inherit) const
{
    check_defined();
    const MethodInfo *mi = getCompatibleMethod(name, args, inherit);
    if (!mi) throw MethodNotFoundException(name, _name);
    return mi->invoke(instance, args);
}

void Type::getAllProperties(PropertyInfoList& props) const
{
    check_defined();
    std::copy(_props.begin(), _props.end(),    std::back_inserter(props));
    for (TypeList::const_iterator i=_base.begin(); i!=_base.end(); ++i)
    {
        (*i)->getAllProperties(props);
    }
}

void Type::getPropertiesMap(PropertyInfoMap& props) const
{
    check_defined();
    props[this] = _props;
    for (TypeList::const_iterator i=_base.begin(); i!=_base.end(); ++i)
    {
        (*i)->getPropertiesMap(props);
    }
}

void Type::getAllMethods(MethodInfoList& methods, FunctionCategory category) const
{
    check_defined();
    const MethodInfoList& input_methods = (category == PUBLIC_FUNCTIONS ? _methods : _protected_methods);
    std::copy(input_methods.begin(), input_methods.end(), std::back_inserter(methods));
    for (TypeList::const_iterator i=_base.begin(); i!=_base.end(); ++i)
    {
        (*i)->getAllMethods(methods, category);
    }
}

void Type::getMethodsMap(MethodInfoMap& methods, FunctionCategory category) const
{
    check_defined();
    methods[this] = (category == PUBLIC_FUNCTIONS ? _methods : _protected_methods);
    for (TypeList::const_iterator i=_base.begin(); i!=_base.end(); ++i)
    {
        (*i)->getMethodsMap(methods, category);
    }
}

Value Type::createInstance(ValueList& args) const
{
    if (isAbstract())
        throw TypeIsAbstractException(_ti);

    const ConstructorInfo *ci = getCompatibleConstructor(args);
    if (!ci)
        throw ConstructorNotFoundException(_ti);

    return ci->createInstance(args);
}

const ConstructorInfo *Type::getCompatibleConstructor(const ValueList& values) const
{
    check_defined();

    typedef std::vector<ConstructorMatch> MatchList;
    MatchList matches;

    int pos = 0;
    for (ConstructorInfoList::const_iterator i=_cons.begin(), e=_cons.end(); i!=e; ++i, ++pos)
    {
        float match;
        if (areArgumentsCompatible(values, (*i)->getParameters(), match))
        {
            ConstructorMatch mm;
            mm.list_pos = pos;
            mm.match = match;
            mm.object = *i;
            matches.push_back(mm);
        }
    }

    if (!matches.empty())
    {
        std::sort(matches.begin(), matches.end());
        return matches.front().object;
    }

    return 0;
}

const ConstructorInfo *Type::getConstructor(const ParameterInfoList& params) const
{
    check_defined();

    for (ConstructorInfoList::const_iterator i=_cons.begin(), e=_cons.end(); i!=e; ++i)
    {
        if (areParametersCompatible(params, (*i)->getParameters()))
            return *i;
    }

    return 0;
}
