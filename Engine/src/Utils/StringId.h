#pragma once

#include "../ZeroEngineStd.h"

// Based on Game Engine Architecture, p.278

namespace ZeroEngine {

    typedef uint32 StringId;

    class StringIdManager {
    private:
        static std::map<StringId, const char*> _string_table;
    public:
        ~StringIdManager() { _string_table.clear(); }
        static StringId intern_string(const char* str);
        static const char* find_string(StringId id);
        static void shutdown();

    private:
        StringIdManager() {}
        StringIdManager(const StringIdManager&) {}
    };

    // Use this macro to create StringId's so
    // that eventually the hashes can be created
    // at compile time rather than runtime.
    #define STRING_ID(str) StringIdManager::intern_string((str))
}