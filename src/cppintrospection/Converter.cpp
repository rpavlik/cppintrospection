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
// cppintrospection - Copyright (C) 2005 Marco Jez

#include <cppintrospection/Converter>

using namespace cppintrospection;

Converter::~Converter()
{
}

CompositeConverter::CompositeConverter(const ConverterList& cvt) : cvt_(cvt)
{
}

CompositeConverter::CompositeConverter(ConverterList& cvt)
{
    cvt_.swap(cvt);
}

CompositeConverter::~CompositeConverter()
{
}

Value CompositeConverter::convert(const Value& src) const
{
    Value accum(src);
    for (ConverterList::const_iterator i = cvt_.begin(), e = cvt_.end(); i != e;
         ++i)
        accum = (*i)->convert(accum);
    return accum;
}

CastType CompositeConverter::getCastType() const
{
    return COMPOSITE_CAST;
}
