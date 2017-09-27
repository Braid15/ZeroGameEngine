#pragma once

#include "IFrameworkFactory.h"

namespace ZeroEngine { namespace Framework {

    class NullFrameworkFactory : public IFrameworkFactory {

    public:
        NullFrameworkFactory();
        ~NullFrameworkFactory();
    };

} }

