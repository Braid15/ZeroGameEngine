#pragma once 

#include "../ZeroEngineStd.h"
#include "IPhysics.h"

namespace ZeroEngine {

    class NullPhysics : public IPhysics {
    public:
        inline void on_update(Ticks delta_time) override {}
        inline void sync_visible_scene() override {}
        inline void render_diagnostics() override {}
        inline StringRepr to_string() const override { return "NullPhysics"; }
    };
}