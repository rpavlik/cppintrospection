/* osgIntrospection example, simple_example.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*  THE SOFTWARE.
*/


#include <osg/ref_ptr>
#include <osgDB/DynamicLibrary>
#include <osgIntrospection/Reflection>
#include <osgIntrospection/Type>
#include <osgIntrospection/MethodInfo>
#include <osgIntrospection/PropertyInfo>
#include <iostream>

using namespace osgIntrospection;

// borrowed from osgDB...
std::string createLibraryNameForWrapper(const std::string& ext)
{
#if defined(WIN32)
    // !! recheck evolving Cygwin DLL extension naming protocols !! NHV
    #ifdef __CYGWIN__
        return "cygwin_osgwrapper_"+ext+".dll";
    #elif defined(__MINGW32__)
        return "mingw_osgwrapper_"+ext+".dll";
    #else
        #ifdef _DEBUG
            return "osgwrapper_"+ext+"d.dll";
        #else
            return "osgwrapper_"+ext+".dll";
        #endif
    #endif
#elif macintosh
    return "osgwrapper_" + ext;
#else
    return "osgwrapper_" + ext + ADDQUOTES(OSG_PLUGIN_EXTENSION);
#endif
}

int checkType( const Type& type )
{
    if ( !type.isDefined() )
    {
        std::cout << "No such type: " << type.getQualifiedName() << std::endl;
        return 1;
    }
    return 0;
}

const MethodInfo* findMethod( const Type& type, const std::string& name, Value* arg1=0, Value* arg2=0 )
{
    ValueList args;
    if ( arg1 ) args.push_back( *arg1 );
    if ( arg2 ) args.push_back( *arg2 );
    const MethodInfo* method = type.getCompatibleMethod(name, args, true);
    if ( !method )
    {
        std::cout << "No such method: " << name << std::endl;
    }
    return method;
}

int main( int argc, char** argv )
{
    // load the library of wrappers that reflect the 
    // classes defined in the 'osg' namespace. In the
    // future this will be done automatically under
    // certain circumstances (like deserialization).
    osg::ref_ptr<osgDB::DynamicLibrary> osg_reflectors = 
        osgDB::DynamicLibrary::loadLibrary(createLibraryNameForWrapper("osg"));
    osg::ref_ptr<osgDB::DynamicLibrary> osgGA_reflectors = 
        osgDB::DynamicLibrary::loadLibrary(createLibraryNameForWrapper("osgGA"));
    osg::ref_ptr<osgDB::DynamicLibrary> osgViewer_reflectors = 
        osgDB::DynamicLibrary::loadLibrary(createLibraryNameForWrapper("osgViewer"));
    
    try
    {
        // Find osg::Vec3 class
        const Type& vec3_type = Reflection::getType("osg::Vec3");
        if ( checkType(vec3_type) ) return 1;
        
        // Find osg::Sphere class
        const Type& sphere_type = Reflection::getType("osg::Sphere");
        if ( checkType(sphere_type) ) return 1;
        
        // Find osg::ShapeDrawable class
        const Type& shapedrawable_type = Reflection::getType("osg::ShapeDrawable");
        if ( checkType(shapedrawable_type) ) return 1;
        
        // Find osg::Geode class
        const Type& geode_type = Reflection::getType("osg::Geode");
        if ( checkType(geode_type) ) return 1;
        
        // Find osgViewer::Viewer class
        const Type& viewer_type = Reflection::getType("osgViewer::Viewer");
        if ( checkType(viewer_type) ) return 1;
        
        // Now, create instances and invoke methods to produce code as following.
        // This process is much more complex than directly using osg libraries,
        // but the program will examine itself to find suitable classes and methods!
        // It will finally create a sphere in the viewer:
        
        // float radius = 1.0f;
        float radius = 1.0f;
        
        // osg::Vec3 center();
        Value center = vec3_type.createInstance();
        
        // osg::Sphere* sphere = new osg::Sphere(center, radius);
        ValueList sphere_args;
        sphere_args.push_back( center );
        sphere_args.push_back( Value(radius) );
        Value sphere = sphere_type.createInstance(sphere_args);
        
        // osg::ShapeDrawable* shapeDrawable = new osg::ShapeDrawable(sphere);
        ValueList shapedrawable_args; shapedrawable_args.push_back( sphere );
        Value shapeDrawable = shapedrawable_type.createInstance(shapedrawable_args);
        
        // osg::Geode* geode = new osg::Geode;
        Value geode = geode_type.createInstance();
        
        // geode->addDrawable( shapeDrawable );
        const MethodInfo* addrawable_method = findMethod(geode_type, "addDrawable", &shapeDrawable);
        if ( addrawable_method )
        {
            ValueList args; args.push_back( shapeDrawable );
            addrawable_method->invoke( geode, args );
        }
        
        // osgViewer::Viewer* viewer = new osgViewer::Viewer;
        Value viewer = viewer_type.createInstance();
        
        // viewer->setSceneData( geode );
        const MethodInfo* setscenedata_method = findMethod(viewer_type, "setSceneData", &geode);
        if ( setscenedata_method )
        {
            ValueList args; args.push_back( geode );
            setscenedata_method->invoke( viewer, args );
        }
        
        // viewer->run();
        const MethodInfo* run_method = findMethod(viewer_type, "run");
        if ( run_method ) run_method->invoke( viewer );
    }
    catch( const osgIntrospection::Exception &e )
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

