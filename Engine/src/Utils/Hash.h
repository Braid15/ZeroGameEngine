#pragma once

#include "../ZeroEngineStd.h"
#include <unordered_map>

namespace ZeroEngine {


    class Hash {
    private:
        class StdHashImpl;
        static StdHashImpl _implementation;
    public:
        static int32 hash(std::string);
        static int32 hash(const char*);
    private:
        Hash() {}
        Hash(const Hash&) {}

        class IHashImpl {
        public:
            virtual int32 hash(std::string) const = 0;
        };

        class StdHashImpl : public IHashImpl {
        public:
            inline int32 hash(std::string str) const override {
                return static_cast<int32>(std::hash<std::string>{}(str));
            }
        };
    };
}