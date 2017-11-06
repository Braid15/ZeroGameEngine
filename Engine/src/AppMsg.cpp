#include "AppMsg.h"

namespace ZeroEngine {

    AppMsgArgs AppMsgArgs::empty = EmptyMsgArgs();

    MemoryPool* AppMsg::_memory_pool = nullptr;


    AppMsgType MouseMsg::type = MOUSE_MSG;
    AppMsgPtr MouseMsg::create(AppMsgArgs args) {
        return new MouseMsg(0);
    }

    AppMsgType QuitMsg::type = QUIT_MSG;
    AppMsgPtr QuitMsg::create(AppMsgArgs args) {
        return new QuitMsg(0);
    }

    AppMsgType NullMsg::type = NULL_MSG;
    AppMsgPtr NullMsg::create(AppMsgArgs args) {
        return new NullMsg(0);
    }

    AppMsgType UnhandledMsg::type = UNHANDLED_MSG;
    AppMsgPtr UnhandledMsg::create(AppMsgArgs args) {
        return new UnhandledMsg(0);
    }


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

    void AppMsg::init_memory_pool() {
        if (_memory_pool == nullptr) {
            _memory_pool = zero_new MemoryPool();
            _memory_pool->initialize(sizeof(AppMsg), 1);
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
    int AppMsg::_allocations = 0;

    void AppMsg::print_creation_data() {
        std::cout << "AppMsg created: " << ++_allocations << " : " << this << "\n";
    }

    void AppMsg::print_deletion_data() {
        std::cout << "AppMsg deleted: " << --_allocations << " : " << this << "\n";
    }
    #endif
}