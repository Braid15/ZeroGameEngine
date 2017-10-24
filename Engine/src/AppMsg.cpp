#include "AppMsg.h"

namespace ZeroEngine {

    int AppMsg::_allocations = 0;
    MemoryPool* AppMsg::_memory_pool = nullptr;

    void* AppMsg::operator new( size_t size ) {
        std::cout << "new from AppMsg\n";
        assert( _memory_pool != nullptr );
        void* memory = _memory_pool->allocate();
        return memory;
    }

    void AppMsg::operator delete( void* ptr ) {
        std::cout << "delete from AppMsg\n";
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



    AppMsgType MouseMsg::type = MOUSE_MSG;

    AppMsgType QuitMsg::type = QUIT_MSG;

    AppMsgArgs AppMsgArgs::empty = EmptyMsgArgs();
}