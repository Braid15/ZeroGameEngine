#pragma once 

#include "../ZeroEngineStd.h"

#include "Entity.h"
#include "EntityComponent.h"
#include "EntityFactory.h"

namespace ZeroEngine {

    class EntityManager : public IZeroObject {
    public:
        bool initialize();
        bool shutdown();
        inline StringRepr to_string() const { return "EntityManager"; }
    };
}
