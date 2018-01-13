#pragma once

#include "../ZeroEngineStd.h"
#include <unordered_map>

namespace ZeroEngine {


    class Hash {
    private:
        class StdHashImpl;
        static StdHashImpl _implementation;
    public:
        static Uint32 hash(std::string);
        static Uint32 hash(const char*);
    private:
        Hash() {}
        Hash(const Hash&) {}

        class IHashImpl {
        public:
            virtual Uint32 hash(std::string) const = 0;
        };

        class StdHashImpl : public IHashImpl {
        public:
            inline Uint32 hash(std::string str) const override {
                return static_cast<Uint32>(std::hash<std::string>{}(str));
            }
        };
    };
}