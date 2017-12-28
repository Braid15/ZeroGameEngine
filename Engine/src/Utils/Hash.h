#pragma once

#include "../ZeroEngineStd.h"
#include <unordered_map>

namespace ZeroEngine {


    class Hash {
    private:
        class StdHashImpl;
        static StdHashImpl _implementation;
    public:
        static uint32 hash(std::string);
        static uint32 hash(const char*);
    private:
        Hash() {}
        Hash(const Hash&) {}

        class IHashImpl {
        public:
            virtual uint32 hash(std::string) const = 0;
        };

        class StdHashImpl : public IHashImpl {
        public:
            inline uint32 hash(std::string str) const override {
                return static_cast<uint32>(std::hash<std::string>{}(str));
            }
        };
    };
}