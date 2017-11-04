#pragma once

#include "ZeroEngineStd.h"
#include "Utils\MemoryPool.h"
#include "AppMsg.h"

namespace ZeroEngine {

    class AppMsgFactory {
        AppMsgPtr _current_message;
        MemoryPool* _memory_pool;
    public:
        AppMsgFactory();
        virtual ~AppMsgFactory();
        AppMsgPtr create_message(AppMsgType);
    private:
        inline AppMsgFactory(const AppMsgFactory&) {}
        void free_current_message();
    };
}