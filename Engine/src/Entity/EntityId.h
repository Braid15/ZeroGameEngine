#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    typedef Uint32 EntityId;

    constexpr EntityId invalid_entity_id() {
        return 0xFFFFFFFF;
    }
}