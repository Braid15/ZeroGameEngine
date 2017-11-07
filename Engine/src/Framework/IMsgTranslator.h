#pragma once 

#include "../ZeroEngineStd.h"
#include "../AppMsg/AppMsg.h"

namespace ZeroEngine {

    typedef unsigned long FrameworkMsgId;

    class IMsgTranslator {
    public:
        virtual AppMsgType translate_message(FrameworkMsgId) = 0;
    };
}