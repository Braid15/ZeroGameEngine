#pragma once

#include "IFrameworkFactory.h"

namespace ZeroEngine {

    class NullFrameworkFactory : public IFrameworkFactory {

    public:
        NullFrameworkFactory();
        ~NullFrameworkFactory();
    };

}

