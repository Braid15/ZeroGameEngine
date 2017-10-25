#include "AppMsg.h"

namespace ZeroEngine {

    AppMsgType MouseMsg::type = MOUSE_MSG;
    AppMsgType QuitMsg::type = QUIT_MSG;
    AppMsgArgs AppMsgArgs::empty = EmptyMsgArgs();
    MemoryPool* AppMsg::_memory_pool = nullptr;

    #ifdef _DEBUG
    int AppMsg::_allocations = 0;

    void AppMsg::print_creation_data() {
        std::cout << "AppMsg created: " << ++_allocations << " : " << this << "\n";
    }

    void AppMsg::print_deletion_data() {
        std::cout << "AppMsg deleted: " << --_allocations << " : " << this << "\n";
    }
    #endif

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

    void* AppMsg::operator new( size_t size ) {
        assert( _memory_pool != nullptr );
        void* memory = _memory_pool->allocate();
        return memory;
    }

    void AppMsg::operator delete( void* ptr ) {
        assert( _memory_pool != nullptr );
        _memory_pool->free( ptr );
    }

    void AppMsg::inititialize_memory_pool( unsigned int chunks, const char* name ) {
        std::cout << "called\n";
        if ( _memory_pool ) {
            delete _memory_pool;
        }

        _memory_pool = new MemoryPool();

        #ifdef _DEBUG
        _memory_pool->set_name( name );
        #endif

        _memory_pool->initialize( sizeof( AppMsg ), chunks );
    }

    void AppMsg::destroy_memory_pool() {
        assert( _memory_pool != nullptr );
        delete _memory_pool;
        _memory_pool = nullptr;
    }



    
}