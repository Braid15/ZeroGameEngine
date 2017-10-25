#pragma once 

#include "../ZeroEngineStd.h"
#include "../Graphics/Point.h"

namespace ZeroEngine {
    
    class GameOptions {
        Point<long> _screen_size;

    public:
        GameOptions();
        inline Point<long> get_screen_size() const { return _screen_size; }
    };
}