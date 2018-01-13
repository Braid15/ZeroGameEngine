#pragma once

#include "../ZeroEngineStd.h"

// Based on Game Engine Architecture, p.278

namespace ZeroEngine {

    typedef Uint32 StringId;

    class StringIdManager {
    private:
        std::map<StringId, const char*> _string_table;
    public:
        static StringIdManager& get_singleton();
        ~StringIdManager() { _string_table.clear(); }
        StringId intern_string(const char* str);
        const char* find_string(StringId id);
        void shutdown();

    private:
        StringIdManager() = default;
        StringIdManager(const StringIdManager&) {}
    };

    // Use this macro to create StringId's so
    // that eventually the hashes can be created
    // at compile time rather than runtime.
    #define STRING_ID(str) StringIdManager::get_singleton().intern_string((str))
}