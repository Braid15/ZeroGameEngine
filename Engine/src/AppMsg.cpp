#include "AppMsg.h"

namespace ZeroEngine {

    AppMsgType MouseMsg::type = MOUSE_MSG;
    AppMsgType QuitMsg::type = QUIT_MSG;
    AppMsgType NullMsg::type = NULL_MSG;
    AppMsgArgs AppMsgArgs::empty = EmptyMsgArgs();

    AppMsg::AppMsg( Time time ) {
        _creation_time = time;
        _args = AppMsgArgs::empty; 

        #ifdef _DEBUG
        print_creation_data();
        #endif
    }

    AppMsg::AppMsg( Time time, AppMsgArgs args ) {
        _creation_time = time;
        _args = args;

        #ifdef _DEBUG
        print_creation_data();
        #endif
    }

    AppMsg::~AppMsg() {
        #ifdef _DEBUG
        print_deletion_data();
        #endif
    }


    #ifdef _DEBUG
    int AppMsg::_allocations = 0;

    void AppMsg::print_creation_data() {
        std::cout << "AppMsg created: " << ++_allocations << " : " << this << "\n";
    }

    void AppMsg::print_deletion_data() {
        std::cout << "AppMsg deleted: " << --_allocations << " : " << this << "\n";
    }
    #endif
}