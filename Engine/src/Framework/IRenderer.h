#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class IRenderer {
        virtual void set_background_color( unsigned int g,
                                           unsigned int b, 
                                           unsigned int r, 
                                           unsigned int a 
        ) = 0;
    };
}