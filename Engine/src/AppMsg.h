#pragma once

#include "ZeroEngineStd.h"
#include "Time.h"
#include "Utils\MemoryPool.h"

// @@TODO: AppMsg needs to take on the responsibliy of deleting instances
// insteade of AppMsgFactory and AppMsg needs to make it so only AppMsgFactory can
// create instances.
// @@TODO: Copyctors for AppMsg
// @@TODO: Seperate file for AppMsgArgs

// !!!
// @@TODO: AppMsgArgs should be using memory pool


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

    // 
    // AppMsgArgs
    // 

    class AppMsgArgs {
    private:
        Time _creation_time;
    public:
        virtual ~AppMsgArgs();
    public:
        inline virtual StringRepr to_string() const = 0;
        inline Time get_creation_time() const { return _creation_time; }
    protected:
        inline AppMsgArgs(Time time) : _creation_time(time) {}
    };

    class EmptyMsgArgs : public AppMsgArgs {
    public:
        inline EmptyMsgArgs(Time time) : AppMsgArgs(time) {}
        inline ~EmptyMsgArgs() {}
        inline StringRepr to_string() const { return "EmptyMsgArgs"; }
    };

    class MouseMotionMsgArgs : public AppMsgArgs {
    public:
        inline MouseMotionMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline StringRepr to_string() const { return "MouseMsgArgs"; }
    };

    class WindowMsgArgs : public AppMsgArgs {
    public:
        inline WindowMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline StringRepr to_string() const { return "WindowMsgArgs"; }
    };



    // 
    // AppMsg classes
    //

    class MemoryPool;

    // @@TODO:
    // So I can switch to shared_ptr at somepoint
    typedef AppMsgArgs* AppMsgArgsPtr;

    // NOTE: AppMsg objects don't call zero_new or zero_delete.
    // Thier new and delete operators are overload to use a memory pool

    class AppMsg : public IZeroObject {
    private:
        static MemoryPool* _memory_pool;
        AppMsgArgsPtr _args;
#ifdef _DEBUG
        static int _allocations;
        void print_creation_data();
        void print_deletion_data();
#endif
    public:
        virtual AppMsgType get_type() const = 0;
        virtual StringRepr to_string() const = 0;
        inline Time get_creation_time() { return _args->get_creation_time(); }
    protected:
        AppMsg(AppMsgArgsPtr);
        virtual ~AppMsg();
        inline AppMsgArgs& get_args() { return *_args; }
        inline void set_args(AppMsgArgsPtr args) { _args = args; }
        static void* operator new(size_t);
        static void* operator new[](size_t);
        static void operator delete(void*);
        static void operator delete[](void*);
        static void init_memory_pool();
        static void destroy_memory_pool();
        friend class AppMsgFactory;
    };


    // @@TODO:
    // So I can switch to shared_ptr at somepoint
    typedef AppMsg* AppMsgPtr;


    class NullMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline StringRepr to_string() const { return "NullMsg"; }
        inline AppMsgType get_type() const { return type; }
        static AppMsgPtr create(AppMsgArgsPtr args);
    protected:
        inline NullMsg(AppMsgArgsPtr args) : AppMsg(args) {}
        inline ~NullMsg() {}
    };


    class MouseMotionMsg : public AppMsg {
    private:
        MouseMotionMsgArgs* _mouse_args;
    public:
        static AppMsgType type;
        inline AppMsgType get_type() const { return type; }
        inline StringRepr to_string() const { return "MouseMotionMsg"; }
        static AppMsgPtr create(AppMsgArgsPtr args);
    protected:
        MouseMotionMsg(AppMsgArgsPtr args);
        inline ~MouseMotionMsg() {}
    };

    class QuitMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline AppMsgType get_type() const { return type; }
        inline StringRepr to_string() const { return "QuitMsg"; }
        static AppMsgPtr create(AppMsgArgsPtr args);
    protected:
        inline QuitMsg(AppMsgArgsPtr args) : AppMsg(args) {}
        inline ~QuitMsg() {}
    };

    class UnhandledMsg : public AppMsg {
    public:
        static AppMsgType type;
        inline AppMsgType get_type() const { return type; }
        inline StringRepr to_string() const { return "UnhandledMsg"; }
        static AppMsgPtr create(AppMsgArgsPtr arg);
    protected:
        inline UnhandledMsg(AppMsgArgsPtr args) : AppMsg(args) {}
        inline ~UnhandledMsg() {}

    };

    class WindowMsg : public AppMsg {
    private:
        WindowMsgArgs* _window_msg_args;
    public:
        static AppMsgType type;
        inline AppMsgType get_type() const { return type; }
        inline StringRepr to_string() const { return "WindowMsg"; }
        static AppMsgPtr create(AppMsgArgsPtr args);
    protected:
        WindowMsg(AppMsgArgsPtr args);
        inline ~WindowMsg() {}
    };




}