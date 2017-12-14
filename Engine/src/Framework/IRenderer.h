#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class IRenderer {
    public:
        virtual void set_background_color( unsigned int g,
                                           unsigned int b, 
                                           unsigned int r, 
                                           unsigned int a 
        ) = 0;
        virtual bool pre_render() = 0;
        virtual void post_render() = 0;
    };

    typedef std::shared_ptr<IRenderer> IRendererPtr;
}