#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class ILoggable : public IZeroObject {

    /* Interface */
    public:
        virtual const std::string get_log_data() const = 0;

    /* IZeroObject */
    public:
        virtual StringRepr to_string() const = 0;
    };
}