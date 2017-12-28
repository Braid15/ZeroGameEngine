#include "MemoryPool.h"

namespace ZeroEngine {

    const static size_t CHUNK_HEADER_SIZE = ( sizeof( unsigned char* ) );

    MemoryPool::MemoryPool() {
        reset();
    }

    MemoryPool::~MemoryPool() {
        destroy();
    }

    bool MemoryPool::initialize( int32 chunk_size, int32 chunk_amount, const char* name) {
        if (_memory_array) {
            destroy();
        }
        _chunk_size = chunk_size;
        _chunk_amount = chunk_amount;
        set_name(name);

        return grow_memory_array();
    }

    void MemoryPool::destroy() {
        #ifdef _DEBUG
        std::string str;
        if ( _allocations != 0 ) {
            str = "***(" + std::to_string( _allocations ) + ")";
        }
        uint64 total_chunks = _chunk_amount * _memory_array_size;
        uint64 wasted_mem = ( total_chunks - _allocation_peak ) * _chunk_size;
        str += "Destroying memory pool: [" + get_name() + ":" + 
            std::to_string( (uint64)_chunk_size ) + "] = " + std::to_string( _allocation_peak ) + 
            "/"  + std::to_string( (uint64)total_chunks ) + " (" + std::to_string( wasted_mem ) +
            " bytes wasted)\n";
        std::cout << str;
        #endif

        for ( int32 i = 0; i < _memory_array_size; ++i ) {
            ::free( _memory_array[ i ] );
        }
        ::free( _memory_array );
        reset();
    }

    void* MemoryPool::allocate() {

        // TODO: I don't like multiple returns
        if ( !_head ) {
            if ( !_allow_resize ) {
                return nullptr;
            }
            if ( !grow_memory_array() ) {
                return nullptr;
            }
        }

        #ifdef _DEBUG
        ++_allocations;
        if ( _allocations > _allocation_peak ) {
            _allocation_peak = _allocations;
        }
        #endif

        unsigned char* ret_memory = _head;
        _head = get_next_block( _head );

        // returns a pointer to the data and not the header chunk
        return (ret_memory + CHUNK_HEADER_SIZE);
    }

    void MemoryPool::free_memory( void* memory ) {
        if ( memory != nullptr ) {
            // gets full  block of memory and not just data section
            unsigned char* block = ((unsigned char*)memory) - CHUNK_HEADER_SIZE;
            set_next_block( block, _head );
            _head = block;

            #ifdef _DEBUG
            --_allocations;
            assert( _allocations >= 0 );
            #endif
        }
    }

    void MemoryPool::reset() {
        _memory_array = nullptr;
        _memory_array_size = 0;
        _head = nullptr;
        _chunk_size = 0;
        _chunk_amount = 0;
        _allow_resize = true;

        #ifdef _DEBUG
        _allocations = 0;
        _allocation_peak = 0;
        #endif
    }

    bool MemoryPool::grow_memory_array() {
        bool success = false;

        #ifdef _DEBUG
        std::string str( "Growing memory pool: [" + get_name() + ":" + 
            std::to_string( (uint64)_chunk_size ) + "] = " + 
            std::to_string( (uint64)_memory_array_size + 1 ) + "\n" );
        // std::cout << str;
        #endif

        size_t allocation_size = sizeof( unsigned char* ) * ( _memory_array_size + 1 );
        unsigned char** new_memory_array =  (unsigned char**)malloc( allocation_size );

        if ( new_memory_array ) {
            // copy existing pointers to new array
            for ( int32 i = 0; i < _memory_array_size; ++i ) {
                new_memory_array[ i ] = _memory_array[ i ];
            }

            // allocate new block of memory
            new_memory_array[ _memory_array_size ] = allocate_new_memory_block();

            // attach new block to the end of memory list
            if ( _head ) {
                unsigned char* current = _head;
                unsigned char* next = get_next_block( _head );
                while ( next ) {
                    current = next;
                    next = get_next_block( next );
                }
                set_next_block( current, new_memory_array[ _memory_array_size ] );
            } else {
                _head = new_memory_array[ _memory_array_size ];
            }

            // destroy old memory array
            if ( _memory_array ) {
                ::free( _memory_array );
            }

            // assign the new memory array and increment the size count
            _memory_array = new_memory_array;
            ++_memory_array_size;
            success = true;
        }

        return success;
    }

    unsigned char* MemoryPool::allocate_new_memory_block() {
        unsigned char* ret_memory = nullptr;

        // calculate size of each block and size of actual memory allocation
        size_t block_size = _chunk_size + CHUNK_HEADER_SIZE;
        size_t true_size = block_size * _chunk_amount;

        // allocate the memory
        unsigned char* new_memory = (unsigned char*)malloc( true_size );

        if ( new_memory ) {
           // turn the memory into a linked list of chunks
            unsigned char* end = new_memory + true_size;
            unsigned char* current = new_memory;

            while ( current < end ) {

                // calculate next pointer position
                unsigned char* next = current + block_size;

                // set next and previous pointers
                unsigned char** chunk_header = (unsigned char**)current;
                chunk_header[ 0 ] = ( next < end ) ? next : nullptr;

                // move to the next block
                current += block_size;
            }
            ret_memory = new_memory;
        }

        return ret_memory;
    }

    unsigned char* MemoryPool::get_next_block( unsigned char* block ) {
        unsigned char** chunk_header = (unsigned char**)block;
        return chunk_header[ 0 ];
    }

    void MemoryPool::set_next_block( unsigned char* block, unsigned char* new_block ) {
        unsigned char** chunk_header = (unsigned char**)block;
        chunk_header[ 0 ] = new_block;
    }
}