#pragma once

#include <typeinfo.h>

// This header does not include ZeroEngineStd.h since that header is include
// into pretty much everything and Type.h will be one of those headers it includes.

namespace ZeroEngine {

    // Helper macro to get objects type
    #define _THIS typeid( this ).name()

    typedef const char* Type;

    // TODO: 10/1/17
    // IType should hold a reference to type_info so that it can 
    // use type_info's overloaded == and != operators
    //
    // Base class that all Zero Engine types will derive from.
    // It will provide an interface for basic operations such as to_string, etc. 
    class IType {

    /* Public Interface */
    public:
        virtual const Type get_type() const = 0;
        virtual const char* to_string() const = 0;
    };
}