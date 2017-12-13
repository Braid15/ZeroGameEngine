#pragma once 

#include "../ZeroEngineStd.h"
#include "IPhysics.h"

namespace ZeroEngine {

    class NullPhysics : public IPhysics {
    public:
        inline StringRepr to_string() const override { return "NullPhysics"; }
    };
}