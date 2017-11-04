#include "GameOptions.h"

namespace ZeroEngine {

    GameOptions::GameOptions() {
        _screen_size = Point<long>( 1024, 768 );
        _vsync_enabled = true;
    }
}