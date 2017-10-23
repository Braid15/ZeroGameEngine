#pragma once

#include <typeinfo.h>

// This header does not include ZeroEngineStd.h since that header is include
// into pretty much everything and Type.h will be one of those headers it includes.

namespace ZeroEngine {

    typedef const char* StringRepr;

    // Base class that all Zero Engine types will derive from.
    class IZeroObject {

    /* Public Interface */
    public:
        virtual StringRepr to_string() const = 0;
    };
}