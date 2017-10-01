#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    typedef const char* FrameworkFactoryID;

    class IFrameworkFactory : public IType {

    public:
        virtual bool initialize() = 0;
        virtual bool shutdown() = 0;
        virtual FrameworkFactoryID get_id() = 0;

    /* IType interface */
    public:
        virtual const Type get_type() const = 0;
        virtual const char* to_string() const = 0;
    };
}
