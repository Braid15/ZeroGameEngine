#pragma once

#include "IZeroObject.h"
#include "Time.h"
#include <iostream>
#include "Utils\MemoryPool.h"

namespace ZeroEngine {

    enum AppMsgType {
        NULL_MSG,
        QUIT_MSG,
        WINDOW_MSG,
        SYSTEM_MSG,
        KEYDOWN_MSG,
        KEYUP_MSG,
        KEYBOARD_MSG,
        MOUSE_MSG,
        MOUSE_MOVE_MSG,
        MOUSE_BUTTON_DOWN_MSG,
        MOUSE_BUTTON_UP_MSG,
        MOUSE_WHEEL_MSG,
        JOY_AXIS_MOTION_MSG,
        JOY_BALL_MOTION_MSG,
        JOY_HAT_MOTION_MSG,
        JOY_BUTTON_DOWN_MSG,
        JOY_BUTTON_UP_MSG,
        JOY_DEVICE_ADDED_MSG,
        JOY_DEVICE_REMOVED_MSG,
        CONTROLLER_AXIS_MOTION_MSG,
        CONTROLLER_BUTTON_DOWN_MSG,
        CONTROLLER_BUTTON_UP_MSG,
        CONTROLLER_DEVICE_ADDED_MSG,
        CONTROLLER_DEVICE_REMOVED_MSG,
        CONTROLLER_DEVICE_REMAPPED_MSG,
        AUDIO_DEVICE_ADDED_MSG,
        AUDIO_DEVICE_REMOVED_MSG,
        RENDER_DEVICE_RESET_MSG,
        RENDER_TARGETS_RESET_MSG
    };

    class AppMsgArgs : public IZeroObject {
    public:
        static AppMsgArgs empty;
        inline virtual ~AppMsgArgs() {}

    /* IZeroObject */
    public:
        inline AppMsgArgs() {}
        inline virtual StringRepr to_string() const { return "AppMsgArgs"; }

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
        static MemoryPool* _memory_pool;
        AppMsgArgs _args;
        Time _creation_time;

    public:
        AppMsg( Time );
        AppMsg( Time, AppMsgArgs );
        virtual ~AppMsg();
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

    #ifdef _DEBUG
    private:
        static int _allocations;
        void print_creation_data();
        void print_deletion_data();
    #endif


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