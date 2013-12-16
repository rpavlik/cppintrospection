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

#include <cppintrospection/GenericReflectorBase>
#include <cppintrospection/MethodInfo> // for MethodInfo
#include <cppintrospection/Reflection> // for Reflection
#include <cppintrospection/Type> // for Type, ConstructorInfoList, etc
#include <utility> // for make_pair

namespace cppintrospection
{
    GenericReflectorBase::GenericReflectorBase(const ExtendedTypeInfo &ti,
                                               const std::string &qname,
                                               bool abstract)
        : _type(Reflection::getOrRegisterType(ti, true))
    {
        if (!_type->_name.empty())
        {
            _type->_aliases.push_back(purify(qname));
        }
        else
        {
            split_qualified_name(purify(qname), _type->_name,
                                 _type->_namespace);
        }
        _type->_is_abstract = abstract;
    }

    GenericReflectorBase::GenericReflectorBase(const ExtendedTypeInfo &ti,
                                               const std::string &name,
                                               const std::string &ns,
                                               bool abstract)
        : _type(Reflection::getOrRegisterType(ti, true))
    {
        if (!_type->_name.empty())
            _type->_aliases.push_back(ns.empty() ? purify(name)
                                                 : purify(ns + "::" + name));
        else
        {
            _type->_name = purify(name);
            _type->_namespace = purify(ns);
        }
        _type->_is_abstract = abstract;
    }

    Type *GenericReflectorBase::registerPtype(const ExtendedTypeInfo &ti,
                                              const ReaderWriter *rw,
                                              const Comparator *cmp)
    {
        Type *ptype = registerRelatedType(ti);
        ptype->_pointed_type = _type;
        ptype->_rw = rw;
        ptype->_cmp = cmp;
        return ptype;
    }

    Type *GenericReflectorBase::registerReftype(const ExtendedTypeInfo &ti)
    {
        Type *ptype = registerRelatedType(ti);
        ptype->_referenced_type = _type;
        return ptype;
    }

    Type *GenericReflectorBase::registerRelatedType(const ExtendedTypeInfo &ti)
    {
        Type *rtype = Reflection::getOrRegisterType(ti, true);
        rtype->_name = _type->_name;
        rtype->_namespace = _type->_namespace;
        rtype->_is_defined = true;
        return rtype;
    }

    std::string GenericReflectorBase::purify(const std::string &s)
    {
        std::string r(s);
        while (true)
        {
            std::string::size_type p = r.find(" COMMA ");
            if (p == std::string::npos) break;
            r.replace(p, 7, ", ");
        };
        return r;
    }

    void GenericReflectorBase::split_qualified_name(const std::string &q,
                                                    std::string &n,
                                                    std::string &ns)
    {
        int templ = 0;
        std::string::size_type split_point = std::string::npos;
        std::string::size_type j = 0;
        for (std::string::const_iterator i = q.begin(), e = q.end(); i != e;
             ++i, ++j)
        {
            if (*i == '<') ++templ;
            if (*i == '>') --templ;
            if (templ == 0)
            {
                if (*i == ':' && (i + 1) != q.end() && *(i + 1) == ':')
                    split_point = j;
            }
        }
        if (split_point == std::string::npos)
        {
            ns.clear();
            n = q;
        }
        else
        {
            n = q.substr(split_point + 2);
            ns = q.substr(0, split_point);
        }
    }

    void GenericReflectorBase::addBaseType(const Type &type)
    {
        _type->_base.push_back(&type);
    }

    PropertyInfo *GenericReflectorBase::addProperty(PropertyInfo *pi)
    {
        _type->_props.push_back(pi);
        return pi;
    }

    MethodInfo *GenericReflectorBase::addMethod(MethodInfo *mi)
    {
        for (TempMethodList::iterator i = _temp_methods.begin(),
                                      e = _temp_methods.end();
             i != e; ++i)
        {
            if (mi->overrides(*i)) return *i;
        }

        _temp_methods.push_back(mi);
        _type->_methods.push_back(mi);
        return mi;
    }

    MethodInfo *GenericReflectorBase::addProtectedMethod(MethodInfo *mi)
    {
        for (TempMethodList::iterator i = _temp_protected_methods.begin(),
                                      e = _temp_protected_methods.end();
             i != e; ++i)
        {
            if (mi->overrides(*i)) return *i;
        }

        _temp_protected_methods.push_back(mi);
        _type->_protected_methods.push_back(mi);
        return mi;
    }

    void GenericReflectorBase::addEnumLabel(int v, const std::string &label,
                                            bool strip_namespace)
    {
        if (strip_namespace)
        {
            std::string::size_type p = label.rfind("::");
            if (p != std::string::npos)
            {
                _type->_labels.insert(std::make_pair(v, label.substr(p + 2)));
                return;
            }
        }
        _type->_labels.insert(std::make_pair(v, label));
    }

    ConstructorInfo *GenericReflectorBase::addConstructor(ConstructorInfo *ci)
    {
        _type->_cons.push_back(ci);
        return ci;
    }

    ConstructorInfo *
    GenericReflectorBase::addProtectedConstructor(ConstructorInfo *ci)
    {
        _type->_protected_cons.push_back(ci);
        return ci;
    }

    std::string GenericReflectorBase::qualifyName(const std::string &name) const
    {
        std::string s;
        if (!_type->_namespace.empty())
        {
            s.append(_type->_namespace);
            s.append("::");
        }
        if (!_type->_name.empty())
        {
            s.append(_type->_name);
            s.append("::");
        }
        s.append(name);
        return s;
    }

    CustomAttributeProvider *
    GenericReflectorBase::addAttribute(const CustomAttribute *attrib)
    {
        return _type->addAttribute(attrib);
    }

    void GenericReflectorBase::setReaderWriter(const ReaderWriter *rw)
    {
        _type->_rw = rw;
    }

    void GenericReflectorBase::setComparator(const Comparator *cmp)
    {
        _type->_cmp = cmp;
    }

    void GenericReflectorBase::setDeclaringFile(const std::string &file) const
    {
        _type->_declaringFile = file;
    }
}
