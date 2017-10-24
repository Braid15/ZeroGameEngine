#pragma once

#include "IZeroObject.h"
#include "Time.h"
#include <iostream>
#include "Utils\MemoryPool.h"

namespace ZeroEngine {

    enum AppMsgType {
        NULL_MSG,
        QUIT_MSG,
        KEYDOWN_MSG,
        KEYUP_MSG,
        KEYBOARD_MSG,
        MOUSE_MSG,
        MOUSE_MOVE_MSG,
        MOUSE_BUTTON_DOWN_MSG,
        MOUSE_BUTTON_UP_MSG,
    };

    class AppMsgArgs : public IZeroObject {
    public:
        static AppMsgArgs empty;
        inline virtual ~AppMsgArgs() {}

    /* IZeroObject */
    public:
        inline virtual StringRepr to_string() const { return "AppMsgArgs"; }

    protected:
        inline AppMsgArgs() {}
    };



    class EmptyMsgArgs : public AppMsgArgs {
    public:
        inline EmptyMsgArgs() : AppMsgArgs() {}
        inline ~EmptyMsgArgs() {}

    /* IZeroObject */
    public:
        inline StringRepr to_string() const override { return "EmptyMsgArgs"; }
    };


    class MemoryPool;

    class AppMsg : public IZeroObject {
        static int _allocations;
        AppMsgArgs _args;
        Time _creation_time;
        static MemoryPool* _memory_pool;

    public:
        inline AppMsg( Time time ): 
            _creation_time( time ),
            _args( AppMsgArgs::empty ) 
        { std::cout << "new: " << ++_allocations << " " << this << std::endl; }
        inline virtual ~AppMsg() { std::cout << "delete: " << --_allocations << " " << this << std::endl; }
        inline Time get_creation_time() { return _creation_time; }
        inline virtual AppMsgType get_type() const { return NULL_MSG; }

        static void* operator new( size_t size );
        static void operator delete( void* ptr );
        static void inititialize_memory_pool( unsigned int chunks, const char* name = "AppMsgPool" );
        static void destroy_memory_pool();


    /* IZeroObject */
    public:
        inline virtual StringRepr to_string() const override { return "NullMsg"; }

    protected:
        inline AppMsgArgs get_args() { return _args; }

    };

    // So I can switch to shared_ptr at somepoint
    typedef AppMsg* AppMsgPtr;


    class MouseMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline MouseMsg( Time time ) : AppMsg( time ) {}

    /* AppMsg */
    public:
        inline AppMsgType get_type() const override { return MOUSE_MSG; }

    /* IZeroObject */
    public:
        inline StringRepr to_string() const override { return "MouseMsg"; }
    };



    class QuitMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline QuitMsg( Time time ) : AppMsg( time ) {}

    /* AppMsg */
    public:
        inline AppMsgType get_type() const override { return QUIT_MSG; }

    /* IZeroObject */
    public:
        inline StringRepr to_string() const override { return "QuitMsg"; }
    };



}