#include "AppMsg.h"

namespace ZeroEngine {

    // @@TODO: MsgArgs in own file

    AppMsgArgs::~AppMsgArgs() {
    }

    MemoryPool* AppMsg::_memory_pool = nullptr;
    #ifdef _DEBUG
    int AppMsg::_allocations = 0;
    #endif

    AppMsg::AppMsg(AppMsgArgsPtr args) {
        _args = args;
        #ifdef _DEBUG
        print_creation_data();
        #endif
    }

    AppMsg::~AppMsg() {
        zero_delete(_args);
        #ifdef _DEBUG
        print_deletion_data();
        #endif
    }

    void AppMsg::init_memory_pool() {
        if (_memory_pool == nullptr) {
            _memory_pool = zero_new MemoryPool();
            // !! @@TODO: Need to find largest derived and base size off of that
            // sizeof(AppMsg) causes heap corruption
            _memory_pool->initialize(64, 1);
        }
    }

    void AppMsg::destroy_memory_pool() {
        if (_memory_pool != nullptr) {
            zero_delete(_memory_pool);
        }
    }

    void* AppMsg::operator new(size_t size) {
        assert(_memory_pool != nullptr);
        void* memory = _memory_pool->allocate();
        return memory;
    }

    void AppMsg::operator delete(void* ptr) {
        assert(_memory_pool != nullptr);
        _memory_pool->free_memory(ptr);
    }

    void AppMsg::operator delete[](void* ptr) {
        assert(_memory_pool != nullptr);
        _memory_pool->free_memory(ptr);
    }

    void* AppMsg::operator new[](size_t size) {
        assert(_memory_pool != nullptr);
        void* memory = _memory_pool->allocate();
        return memory;
    }

    #ifdef _DEBUG
    void AppMsg::print_creation_data() {
        std::cout << "AppMsg created: " << ++_allocations << " : " << this << "\n";
    }

    void AppMsg::print_deletion_data() {
        std::cout << "AppMsg deleted: " << --_allocations << " : " << this << "\n";
    }
    #endif



    AppMsgType NullMsg::type = NULL_MSG;
    AppMsgPtr NullMsg::create(AppMsgArgsPtr args) {
        return new NullMsg(args);
    }


    AppMsgType MouseMotionMsg::type = MOUSE_MOTION_MSG;
    AppMsgPtr MouseMotionMsg::create(AppMsgArgsPtr args) {
        return new MouseMotionMsg(args);
    }

    MouseMotionMsg::MouseMotionMsg(AppMsgArgsPtr args) : AppMsg(args) {
        _mouse_args = dynamic_cast<MouseMotionMsgArgs*>(args);
    }

    AppMsgType QuitMsg::type = QUIT_MSG;
    AppMsgPtr QuitMsg::create(AppMsgArgsPtr args) {
        return new QuitMsg(args);
    }


    AppMsgType UnhandledMsg::type = UNHANDLED_MSG;
    AppMsgPtr UnhandledMsg::create(AppMsgArgsPtr args) {
        return new UnhandledMsg(args);
    }

    AppMsgType WindowMsg::type = WINDOW_MSG;
    AppMsgPtr WindowMsg::create(AppMsgArgsPtr args) {
        return new WindowMsg(args);
    }

    WindowMsg::WindowMsg(AppMsgArgsPtr args) : AppMsg(args) {
        _window_msg_args = dynamic_cast<WindowMsgArgs*>(args);
    }
}