#pragma once

#include <typeinfo.h>

// This header does not include ZeroEngineStd.h since that header is include
// into pretty much everything and Type.h will be one of those headers it includes.

namespace ZeroEngine {

    typedef const char* TypeName;

    // Base class that all Zero Engine types will derive from.
    class IType {

    /* Public Interface */
    public:
        virtual TypeName get_type() const = 0;
    };
}