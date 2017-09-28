#pragma once

#include "../ZeroEngineStd.h"
#include "IFrameworkFactory.h"


namespace ZeroEngine {

    class BaseFrameworkFactory : public IFrameworkFactory {

    public:
        virtual bool Initialize() = 0;
        virtual bool Shutdown() = 0;

    public:
        BaseFrameworkFactory( FrameworkFactoryID id );
        virtual ~BaseFrameworkFactory();
        virtual FrameworkFactoryID GetID() override;

    private:
        FrameworkFactoryID _id;
    };
}