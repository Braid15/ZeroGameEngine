#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    // @@TODO: 9/27/2017
    // I want this class to make it so that logging
    // can be a bit easier and a class can just pass itself
    // to the logger. Don't know how I want to implement it
    class ILoggable {

    public:
        virtual std::string& GetLogMessage() = 0;
    };
}