#pragma once 

#include "../ZeroEngineStd.h"
#include "../Time.h"

namespace ZeroEngine {

    class IPhysics : public IZeroObject {
    public:
        virtual void on_update(Ticks delta_time) = 0;
        virtual void sync_visible_scene() = 0;
        virtual void render_diagnostics() = 0;
        virtual StringRepr to_string() const = 0;
        virtual ~IPhysics() {}
    };

    typedef std::shared_ptr<IPhysics> IPhysicsPtr;
}