#pragma once

#include "../../ZeroEngineStd.h"
#include "../../3rdParty/SDL/SDL.h"
#include "../BaseFrameworkFactory.h"

namespace ZeroEngine {

    class SDLFrameworkFactory : public BaseFrameworkFactory {

    public:
        SDLFrameworkFactory();
        virtual ~SDLFrameworkFactory();
        virtual bool Initialize() override;
        virtual bool Shutdown() override;
    };
}
