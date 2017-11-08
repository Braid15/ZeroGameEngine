#pragma once 

#include "../ZeroEngineStd.h"
#include "AppMsgArgs.h"
#include "AppMsg.h"

namespace ZeroEngine {

  typedef AppMsg* (*app_msg_creation_delegate)(AppMsgAccessKey&, AppMsgArgs*);

    class AppMsgFactory final {
    private:
        std::map<AppMsgType, app_msg_creation_delegate>* _creation_map;
        AppMsg* _current_message;
        AppMsgAccessKey _access_key;
    public:
        AppMsgFactory();
        ~AppMsgFactory();
        AppMsg* create_message(AppMsgType);
        AppMsg* create_message(AppMsgType, AppMsgArgs*);
    private:
        inline AppMsgFactory(const AppMsgFactory&) {}
        void register_app_messages();
        AppMsg* get_app_message(AppMsgType);
    };
}