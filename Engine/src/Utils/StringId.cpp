#include "StringId.h"

#include "Hash.h"

namespace ZeroEngine {

    static std::map<StringId, const char*> _string_table; 

    StringId intern_string(const char* str) {
        StringId id = Hash::hash(str);
        std::map<StringId, const char*>::iterator it = _string_table.find(id);

        if (it == _string_table.end()) {
            _string_table[id] = strdup(str);
        }

        return id;
    }

    #ifdef _DEBUG
    const char* find_string(StringId id) {
        std::map<StringId, const char*>::iterator it = _string_table.find(id);

        if (it == _string_table.end()) return "";

        return it->second;
    }
    #endif

}