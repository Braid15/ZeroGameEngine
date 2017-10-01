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
        virtual const Type get_type() const override { return _THIS; }
        virtual const char* to_string() const override { return "BaseFrameworkFactory"; }

    private:
        FrameworkFactoryID _id;
    };
}