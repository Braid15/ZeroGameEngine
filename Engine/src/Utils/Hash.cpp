#include "Hash.h"

namespace ZeroEngine {

    Hash::StdHashImpl Hash::_implementation;

    int32_t Hash::hash(std::string str) {
        return _implementation.hash(str);
    }

    int32_t Hash::hash(const char* str) {
        return _implementation.hash(std::string(str));
    }
}