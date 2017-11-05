#pragma once

#include "ZeroEngineStd.h"
#include "AppMsg.h"
#include "3rdParty/SDL/SDL.h"

namespace ZeroEngine {

    class IMessageTranslator {
    public:
        virtual AppMsgType translate_message(FrameworkMessageId) = 0;
    };
}