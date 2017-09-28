#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    typedef const char* FrameworkFactoryID;

    class IFrameworkFactory {

    public:
        virtual bool Initialize() = 0;
        virtual bool Shutdown() = 0;
        virtual FrameworkFactoryID GetID() = 0;
    };
}
