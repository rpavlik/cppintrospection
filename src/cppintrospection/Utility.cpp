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

#include <cppintrospection/Utility>
#include <cppintrospection/ParameterInfo>  // for ParameterInfo
#include <cppintrospection/Value>       // for ValueList, Value

#include <vector>                       // for vector, etc


using namespace cppintrospection;

bool cppintrospection::areParametersCompatible(const ParameterInfoList& pl1, const ParameterInfoList& pl2)
{
    if (pl1.size() == pl2.size())
    {
        if (pl1.empty()) 
            return true;

        ParameterInfoList::const_iterator i1 = pl1.begin();
        ParameterInfoList::const_iterator e1 = pl1.end();
        ParameterInfoList::const_iterator i2 = pl2.begin();

        for (; i1!=e1; ++i1, ++i2)
        {
            const ParameterInfo &p1 = **i1;
            const ParameterInfo &p2 = **i2;
            if (p1.getParameterType() == p2.getParameterType() && 
                p1.getAttributes() == p2.getAttributes())
            {
                return true;
            }
        }
    }

    return false;
}

bool cppintrospection::areArgumentsCompatible(const ValueList& vl, const ParameterInfoList& pl, float &match)
{
    if (pl.empty())
    {
        if (vl.empty())
        {
            match = 1.0f;
            return true;
        }
        return false;
    }

    ParameterInfoList::const_iterator pi = pl.begin();
    ParameterInfoList::const_iterator pe = pl.end();
    ValueList::const_iterator vi = vl.begin();
    ValueList::const_iterator ve = vl.end();

    int exact_args = 0;

    for (; pi != pe; ++pi)
    {
        if (vi == ve)
        {
            // We have run out of values - all remaining parameters must have defaults.
            if ((*pi)->getDefaultValue().isEmpty())
                return false;
            continue;
        }

        if ((*pi)->getParameterType() == vi->getType())
        {
            // Exact match.
            ++exact_args;
        }
        else if (vi->tryConvertTo((*pi)->getParameterType()).isEmpty())
        {
            // Convertible match failed
            return false;
        }

        ++vi;
    }

    match = static_cast<float>(exact_args) / pl.size();
    return true;
}

