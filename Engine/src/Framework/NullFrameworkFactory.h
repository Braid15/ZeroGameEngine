#pragma once

#include "../ZeroEngineStd.h"
#include "BaseFrameworkFactory.h"

namespace ZeroEngine {

    class NullFrameworkFactory : public BaseFrameworkFactory {

    public:
        NullFrameworkFactory();
        ~NullFrameworkFactory();
        bool Initialize() override;
        bool Shutdown() override;
    };

}

