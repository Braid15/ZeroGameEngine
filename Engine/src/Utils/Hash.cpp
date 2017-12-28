#include "Hash.h"

namespace ZeroEngine {

    Hash::StdHashImpl Hash::_implementation;

    uint32 Hash::hash(std::string str) {
        return _implementation.hash(str);
    }

    uint32 Hash::hash(const char* str) {
        return _implementation.hash(std::string(str));
    }
}