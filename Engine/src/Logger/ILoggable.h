#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class ILoggable : public IType {

    /* Interface */
    public:
        virtual const std::string get_log_data() const = 0;

    /* IType interface */
    public:
        virtual TypeName get_type() const = 0;
    };
}