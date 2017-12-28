#pragma once 

#include "../ZeroEngineStd.h"
#include "../Graphics/Point.h"

namespace ZeroEngine {
    
    class GameOptions {
        Point<int32> _screen_size;
        bool _vsync_enabled;

    public:
        GameOptions();
        inline Point<int32> get_screen_size() const { return _screen_size; }
        inline bool is_vsync_enabled() { return _vsync_enabled; }
    };
}