#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Utils/MemoryPool.h"
#include "AppMsgArgs.h"

// @@TODO: AppMsg needs to take on the responsibliy of deleting instances
// insteade of AppMsgFactory and AppMsg needs to make it so only AppMsgFactory can
// create instances.
// @@TODO: Copyctors for AppMs

// @@TODO: Need some kind of referencing system since I won't be using share_ptr
// @@TODO: Who destroys MsgArgs*? AppMsg class or AppMsgArgs* creator? 


namespace ZeroEngine {

    typedef uint8_t AppMsgType;

    class AppMsg : public IZeroObject {
    private:
        static MemoryPool* _memory_pool;
        AppMsgArgs* _args;
#ifdef _DEBUG
        static int _allocations;
        void print_creation_data();
        void print_deletion_data();
#endif
    public:
        virtual const AppMsgType get_type() const = 0;
        virtual StringRepr to_string() const = 0;
        inline Time get_creation_time() { return _args->get_creation_time(); }

        static const AppMsgType null;
        static const AppMsgType quit;
        static const AppMsgType unhandled;
        static const AppMsgType window;
        static const AppMsgType system;
        static const AppMsgType keydown;
        static const AppMsgType keyup;
        static const AppMsgType text_edit;
        static const AppMsgType text_input;
        static const AppMsgType keymap_changed;
        static const AppMsgType mouse_motion;
        static const AppMsgType mouse_button_down;
        static const AppMsgType mouse_button_up;
        static const AppMsgType mouse_wheel;
        static const AppMsgType joy_axis_motion;
        static const AppMsgType joy_ball_motion;
        static const AppMsgType joy_hat_motion;
        static const AppMsgType joy_button_down;
        static const AppMsgType joy_button_up;
        static const AppMsgType joy_device_added;
        static const AppMsgType joy_device_removed;
        static const AppMsgType controller_axis_motion;
        static const AppMsgType controller_button_down;
        static const AppMsgType controller_button_up;
        static const AppMsgType controller_device_added;
        static const AppMsgType controller_device_removed;
        static const AppMsgType controller_device_remapped;
        static const AppMsgType finger_down;
        static const AppMsgType finger_up;
        static const AppMsgType finger_motion;
        static const AppMsgType clipboard;
        static const AppMsgType drop_file;
        static const AppMsgType drop_text;
        static const AppMsgType drop_begin;
        static const AppMsgType drop_complete;
        static const AppMsgType audio_device_added;
        static const AppMsgType audio_device_removed;
        static const AppMsgType render_targets_reset;
        static const AppMsgType render_device_reset;

    protected:
        AppMsg(AppMsgArgs*);
        virtual ~AppMsg();
        inline AppMsgArgs& get_args() { return *_args; }
        inline void set_args(AppMsgArgs* args) { _args = args; }
        static void* operator new(size_t);
        static void* operator new[](size_t);
        static void operator delete(void*);
        static void operator delete[](void*);
        static void init_memory_pool();
        static void destroy_memory_pool();
        friend class AppMsgFactory;
    };

    class NullMsg : public AppMsg {
    public:
        inline StringRepr to_string() const { return "NullMsg"; }
        inline const AppMsgType get_type() const { return AppMsg::null; }
        static AppMsg* create(AppMsgArgs* args);
    protected:
        inline NullMsg(AppMsgArgs* args) : AppMsg(args) {}
        inline ~NullMsg() {}
    };


    class MouseMotionMsg : public AppMsg {
    private:
        MouseMotionMsgArgs* _mouse_args;
    public:
        inline const AppMsgType get_type() const { return AppMsg::mouse_motion; }
        inline StringRepr to_string() const { return "MouseMotionMsg"; }
        static AppMsg* create(AppMsgArgs* args);
    protected:
        MouseMotionMsg(AppMsgArgs* args);
        inline ~MouseMotionMsg() {}
    };

    class QuitMsg : public AppMsg {
    public:
        inline const AppMsgType get_type() const { return AppMsg::quit; }
        inline StringRepr to_string() const { return "QuitMsg"; }
        static AppMsg* create(AppMsgArgs* args);
    protected:
        inline QuitMsg(AppMsgArgs* args) : AppMsg(args) {}
        inline ~QuitMsg() {}
    };

    class UnhandledMsg : public AppMsg {
    public:
        inline const AppMsgType get_type() const { return AppMsg::unhandled; }
        inline StringRepr to_string() const { return "UnhandledMsg"; }
        static AppMsg* create(AppMsgArgs* arg);
    protected:
        inline UnhandledMsg(AppMsgArgs* args) : AppMsg(args) {}
        inline ~UnhandledMsg() {}

    };

    class WindowMsg : public AppMsg {
    private:
        WindowMsgArgs* _window_msg_args;
    public:
        inline const AppMsgType get_type() const { return AppMsg::window; }
        inline StringRepr to_string() const { return "WindowMsg"; }
        static AppMsg* create(AppMsgArgs* args);
    protected:
        WindowMsg(AppMsgArgs* args);
        inline ~WindowMsg() {}
    };

    class SystemMsg : public AppMsg {
    private:
        SystemMsgArgs* _system_msg_args;
    public:
        inline const AppMsgType get_type() const { return AppMsg::system; }
        inline StringRepr to_string() const { return "SystemMsg"; }
        static AppMsg* create(AppMsgArgs* args);
    protected:
        SystemMsg(AppMsgArgs* args);
        inline ~SystemMsg() {}
    };

    class KeyDownMsg : public AppMsg {
    private:
        KeyDownMsgArgs* _keydown_msg_args;
    public:
        inline const AppMsgType get_type() const { return AppMsg::keydown; }
        inline StringRepr to_string() const { return "KeyDownMsg"; }
        static AppMsg* create(AppMsgArgs* args);
    protected:
        KeyDownMsg(AppMsgArgs* args);
        inline ~KeyDownMsg() {}
    };

    class KeyUpMsg : public AppMsg {
    private:
        KeyUpMsgArgs* _key_up_msg_args;
    public:
        inline const AppMsgType get_type() const { return AppMsg::keyup; }
        inline StringRepr to_string() const { return "KeyUpMsg"; }
        static AppMsg* create(AppMsgArgs* args);
    protected:
        KeyUpMsg(AppMsgArgs* args);
        inline ~KeyUpMsg() {}

    };
}