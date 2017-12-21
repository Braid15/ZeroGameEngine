#pragma once

#include "../ZeroEngineStd.h"

// @TODO: Move to Memory folder

// 
// This class is taken from GCC v4
// 

namespace ZeroEngine {

    class MemoryPool {
        unsigned char** _memory_array;
        unsigned int _memory_array_size;
        unsigned char* _head;
        unsigned int _chunk_size;
        unsigned int _chunk_amount;
        bool _allow_resize;

        #ifdef _DEBUG
        unsigned int _allocations;
        unsigned int _allocation_peak;
        std::string _name;
        #endif

    public:
        MemoryPool();
        ~MemoryPool();
        bool initialize(unsigned int chunk_size, 
                        unsigned int chunk_amount,
                        const char* name="MemoryPool"
        );
        void destroy();
        void* allocate();
        void free_memory( void* memory );
        inline unsigned int get_chunk_size() const { return _chunk_size; }
        inline void set_all_resize( bool allow ) { _allow_resize = allow; }

        #ifdef _DEBUG
        inline std::string get_name() const { return _name; }
        inline void set_name( std::string name ) { _name = name; }
        inline void set_name( const char* name ) { _name = name; }
        #endif

    private:
        void reset();
        bool grow_memory_array();
        unsigned char* allocate_new_memory_block();
        unsigned char* get_next_block( unsigned char* block );
        void set_next_block( unsigned char* block, unsigned char* next_block );
        // No copy ctor
        inline MemoryPool( const MemoryPool& mem_pool ) {}
    };
}