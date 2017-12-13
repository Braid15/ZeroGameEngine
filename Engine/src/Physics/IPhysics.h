#pragma once 

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class IPhysics : public IZeroObject {
    public:
        virtual StringRepr to_string() const = 0;
    };

    typedef std::shared_ptr<IPhysics> IPhysicsPtr;
}