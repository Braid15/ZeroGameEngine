#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class ILoggable : public IType {

    /* Interface */
    public:
        virtual const std::string get_log_data() const = 0;

    /* IType interface */
    public:
        virtual const TypeID get_type() const = 0;
        virtual const char* to_string() const = 0;
    };
}