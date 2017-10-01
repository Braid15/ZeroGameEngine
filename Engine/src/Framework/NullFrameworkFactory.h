#pragma once

#include "../ZeroEngineStd.h"
#include "BaseFrameworkFactory.h"

namespace ZeroEngine {

    class NullFrameworkFactory : public BaseFrameworkFactory {

    public:
        NullFrameworkFactory();
        ~NullFrameworkFactory();
        bool initialize() override;
        bool shutdown() override;

    /* IType interface */
    public:
        virtual TypeName get_type() const override { return "NullFrameworkFactory"; }
    };

}

