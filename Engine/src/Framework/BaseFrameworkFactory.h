#pragma once

#include "../ZeroEngineStd.h"
#include "IFrameworkFactory.h"


namespace ZeroEngine {

    class BaseFrameworkFactory : public IFrameworkFactory {

    public:
        virtual bool initialize() = 0;
        virtual bool shutdown() = 0;

    public:
        BaseFrameworkFactory( FrameworkFactoryID id );
        virtual ~BaseFrameworkFactory();
        virtual FrameworkFactoryID get_id() override;

    /* IType interface */
    public: 
        virtual TypeName get_type() const override { return "BaseFrameworkFactory"; }

    private:
        FrameworkFactoryID _id;
    };
}