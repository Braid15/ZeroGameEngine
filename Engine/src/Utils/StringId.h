#pragma once

#include "../ZeroEngineStd.h"

// Based on Game Engine Architecture, p.278

namespace ZeroEngine {

    typedef uint32 StringId;

    extern StringId intern_string(const char* str);

    // This should only be used for debugging purposes.
    // At runtime the engine should only be using StringIds.
    #ifdef _DEBUG
    extern const char* find_string(StringId id);
    #endif

    // @@TODO:
    // Use this macro to create StringId's so
    // that eventually the hashes can be created
    // at compile time rather than runtime.
    #define STRING_ID(str) intern_string((str))
}