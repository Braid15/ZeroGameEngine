#include "StringId.h"
#include "Hash.h"

namespace ZeroEngine {

    StringIdManager& StringIdManager::get_singleton() {
        static StringIdManager singleton;
        return singleton;
    }

    StringId StringIdManager::intern_string(const char* str) {
        StringId id = Hash::hash(str);

        std::map<StringId, const char*>::iterator it = _string_table.find(id);

        if (it == _string_table.end()) {
            _string_table[id] = zero_strdup(str);
        }

        return id;
    }

    const char* StringIdManager::find_string(StringId id) {
        std::map<StringId, const char*>::iterator it = _string_table.find(id);

        if (it == _string_table.end()) return "";

        return it->second;
    }

    void StringIdManager::shutdown() {
        std::map<StringId, const char*>::iterator it = _string_table.begin();
        while (it != _string_table.end()) {
            if (it->second) {
                zero_free((void*)it->second);
                it->second = nullptr;
            }
            _string_table.erase(it++);
        }
    }
}