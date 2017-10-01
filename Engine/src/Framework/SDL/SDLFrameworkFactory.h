#pragma once

#include "../../ZeroEngineStd.h"
#include "../../3rdParty/SDL/SDL.h"
#include "../BaseFrameworkFactory.h"

namespace ZeroEngine {

    class SDLFrameworkFactory : public BaseFrameworkFactory {

    public:
        SDLFrameworkFactory();
        virtual ~SDLFrameworkFactory();
        virtual bool initialize() override;
        virtual bool shutdown() override;

    /* IType interface */
    public:
        virtual const TypeID get_type() const override { return _THIS; }
        virtual const char* to_string() const override { return "SDLFrameworkFactory"; }
    };
}
