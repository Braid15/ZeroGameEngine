#pragma once

#include "ZeroEngineStd.h"
#include "Time.h"
#include "Utils\MemoryPool.h"

namespace ZeroEngine {

    typedef uint32_t FrameworkMessageId;

      enum AppMsgType {
        MSG_BEGIN,
        NULL_MSG,
        QUIT_MSG,
        UNHANDLED_MSG,
        WINDOW_MSG,
        SYSTEM_MSG,
        KEYDOWN_MSG,
        KEYUP_MSG,
        KEYBOARD_MSG,
        TEXT_EDIT_MSG,
        TEXT_INPUT_MSG,
        KEYMAP_CHANGE_MSG,
        MOUSE_MSG,
        MOUSE_MOTION_MSG,
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
        FINGER_DOWN_MSG,
        FINGER_UP_MSG,
        FINGER_MOTION_MSG,
        CLIPBOARD_MSG,
        DROP_FILE_MSG,
        DROP_TEXT_MSG,
        DROP_BEGIN_MSG,
        DROP_COMPLETE_MSG,
        AUDIO_DEVICE_ADDED_MSG,
        AUDIO_DEVICE_REMOVED_MSG,
        RENDER_TARGETS_RESET_MSG,
        RENDER_DEVICE_RESET_MSG,
        MSG_END
    };

    
    class AppMsgArgs : public IZeroObject {
    public:
        static AppMsgArgs empty;
        inline virtual ~AppMsgArgs() {}

    public:
        inline AppMsgArgs() {}
        inline virtual StringRepr to_string() const { return "AppMsgArgs"; }

    };

    class EmptyMsgArgs : public AppMsgArgs {
    public:
        inline EmptyMsgArgs() : AppMsgArgs() {}
        inline ~EmptyMsgArgs() {}
        inline StringRepr to_string() const override { return "EmptyMsgArgs"; }
    };

    class MemoryPool;

    // NOTE: AppMsg objects don't call zero_new or zero_delete.
    // Thier new and delete operators are overload to use a memory pool

    class AppMsg : public IZeroObject {
    private:
        static MemoryPool* _memory_pool;
        AppMsgArgs _args;
        Time _creation_time;
    public:
        inline Time get_creation_time() { return _creation_time; }
        virtual AppMsgType get_type() const = 0;
        virtual StringRepr to_string() const = 0;
        bool can_create(AppMsgType type) const { return type == get_type(); }
    protected:
        friend class AppMsgFactory;
        AppMsg( Time );
        AppMsg( Time, AppMsgArgs );
        virtual ~AppMsg();
        inline AppMsgArgs get_args() { return _args; }
        inline void set_args(AppMsgArgs args) { _args = args; }
        static void* operator new(size_t);
        static void* operator new[](size_t);
        static void operator delete(void*);
        static void operator delete[](void*);
        static void init_memory_pool();
        static void destroy_memory_pool();

    #ifdef _DEBUG
    private:
        static int _allocations;
        void print_creation_data();
        void print_deletion_data();
    #endif
    };


    // TEMP:
    // So I can switch to shared_ptr at somepoint
    typedef AppMsg* AppMsgPtr;


    class NullMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline StringRepr to_string() const { return "NullMsg"; }
        inline AppMsgType get_type() const { return type; }
        static AppMsgPtr create(AppMsgArgs args);
    protected:
        inline NullMsg(Time time) : AppMsg(time) {}
        inline ~NullMsg() {}
    };


    class MouseMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline AppMsgType get_type() const { return type; }
        inline StringRepr to_string() const { return "MouseMsg"; }
        static AppMsgPtr create(AppMsgArgs args);
    protected:
        inline MouseMsg( Time time ) : AppMsg( time ) {}
        inline ~MouseMsg() {}
    };



    class QuitMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline AppMsgType get_type() const { return type; }
        inline StringRepr to_string() const { return "QuitMsg"; }
        static AppMsgPtr create(AppMsgArgs args);
    protected:
        inline QuitMsg( Time time ) : AppMsg( time ) {}
        inline ~QuitMsg() {}
    };

    class UnhandledMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline AppMsgType get_type() const { return type; }
        inline StringRepr to_string() const { return "UnhandledMsg"; }
        static AppMsgPtr create(AppMsgArgs arg);
    protected:
        inline UnhandledMsg(Time time) : AppMsg(time) {}
        inline ~UnhandledMsg() {}

    };


}