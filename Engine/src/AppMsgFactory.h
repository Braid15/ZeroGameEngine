#pragma once

#include "ZeroEngineStd.h"
#include "AppMsg.h"

namespace ZeroEngine {

    typedef AppMsgPtr (*app_msg_creation_delegate)(AppMsgArgs);

    class AppMsgFactory {
    private:
        std::map<AppMsgType, app_msg_creation_delegate>* _creation_map;
        AppMsgPtr _current_message;
    public:
        AppMsgFactory();
        virtual ~AppMsgFactory();
        AppMsgPtr create_message(AppMsgType);
        AppMsgPtr create_message(AppMsgType, AppMsgArgs);
    private:
        inline AppMsgFactory(const AppMsgFactory&) {}
        void register_app_messages();
        AppMsgPtr get_app_message(AppMsgType);
    };
}