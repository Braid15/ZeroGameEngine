#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Utils/MemoryPool.h"
#include "AppMsgArgs.h"


//
// AppMsgFactory is a friend class to all AppMsg types to give it access to the protected static create() method.
// AppMsgFactory is not a friend class to base AppMsg class, which means that it cannot call the new or delete
// operators explicitly, but must do so through the static methods.



// @@TODO: AppMsg needs to take on the responsibliy of deleting instances
// insteade of AppMsgFactory and AppMsg needs to make it so only AppMsgFactory can
// create instances.
// @@TODO: Copyctors for AppMs

// @@TODO: Need some kind of referencing system since I won't be using share_ptr
// @@TODO: Who destroys MsgArgs*? AppMsg class or AppMsgArgs* creator? 


namespace ZeroEngine {

    typedef uint8_t AppMsgType;

    //
    // AppMsgAccessKey
    //
    //
    // Only friend classes of AppMsgAccessKey can instantiate it and an instance of AppMsgAccessKey is need
    // to access certain methods in AppMsg types.
    //

    class AppMsgAccessKey final : public IZeroObject {
    private:
        friend class AppMsgFactory;
        inline AppMsgAccessKey() {}
        inline ~AppMsgAccessKey() {}
        inline AppMsgAccessKey(const AppMsgAccessKey&) {}
    public:
        inline StringRepr to_string() const override { return "AppMsgAccessKey"; }
    };

    //
    // AppMsg
    //

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
        inline Time get_time_stamp() { return _args->get_creation_time(); }
        virtual inline void set_args(AppMsgAccessKey&, AppMsgArgs* args) { _args = args; }
        static void destroy(AppMsgAccessKey& key, AppMsg* msg) { delete msg; }
        static void init_memory_pool(AppMsgAccessKey&);
        static void destroy_memory_pool(AppMsgAccessKey&);

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
        static void* operator new(size_t);
        static void* operator new[](size_t);
        static void operator delete(void*);
        static void operator delete[](void*);
    };

    //
    // NullMsg
    //

    class NullMsg final : public AppMsg {
    public:
        inline StringRepr to_string() const override { return "NullMsg"; }
        inline const AppMsgType get_type() const override { return AppMsg::null; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~NullMsg() {}
    private:
        inline NullMsg(AppMsgArgs* args) : AppMsg(args) {}
    };

    //
    // QuitMsg
    //

    class QuitMsg final : public AppMsg {
    public:
        inline const AppMsgType get_type() const override { return AppMsg::quit; }
        inline StringRepr to_string() const override { return "QuitMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~QuitMsg() {}
    private:
        inline QuitMsg(AppMsgArgs* args) : AppMsg(args) {}
    };

    //
    // UnhandledMsg
    //

    class UnhandledMsg final : public AppMsg {
    public:
        inline const AppMsgType get_type() const override { return AppMsg::unhandled; }
        inline StringRepr to_string() const override { return "UnhandledMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~UnhandledMsg() {}
    private:
        inline UnhandledMsg(AppMsgArgs* args) : AppMsg(args) {}
    };

    //
    // WindowMsg
    //

    class WindowMsg final : public AppMsg {
    private:
        WindowMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::window; }
        inline StringRepr to_string() const override { return "WindowMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~WindowMsg() {}
    private:
        WindowMsg(AppMsgArgs*);
    };

    //
    // SystemMsg
    //

    class SystemMsg final : public AppMsg {
    private:
        SystemMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::system; }
        inline StringRepr to_string() const override { return "SystemMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~SystemMsg() {}
    private:
        SystemMsg(AppMsgArgs*);
    };

    //
    // KeyDownMsg
    //

    class KeyDownMsg final : public AppMsg {
    private:
        KeyboardMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::keydown; }
        inline StringRepr to_string() const override { return "KeyDownMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~KeyDownMsg() {}
    private:
        KeyDownMsg(AppMsgArgs*);
    };

    //
    // KeyUpMsg
    //

    class KeyUpMsg final : public AppMsg {
    private:
        KeyboardMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::keyup; }
        inline StringRepr to_string() const override { return "KeyUpMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~KeyUpMsg() {}
    private:
        KeyUpMsg(AppMsgArgs*);
    };

    //
    // TextEditMsg
    //

    class TextEditMsg final : public AppMsg {
    private:
        TextEditMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::text_edit; }
        inline StringRepr to_string() const override { return "TextEditMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~TextEditMsg() {}
    private:
        TextEditMsg(AppMsgArgs*);
    };

    //
    // TextInputMsg
    //

    class TextInputMsg final : public AppMsg {
    private:
        TextInputMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::text_input; }
        inline StringRepr to_string() const override { return "TextInputMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~TextInputMsg() {}
    private:
        TextInputMsg(AppMsgArgs*);
    };

    // 
    // KeyMapChangedMsg
    // 

    class KeyMapChangedMsg final : public AppMsg {
    private:
        KeyMapChangedMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::keymap_changed; }
        inline StringRepr to_string() const override { return "KeyMapChangedMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~KeyMapChangedMsg() {}
    private:
        KeyMapChangedMsg(AppMsgArgs*);
    };

    //
    // MouseButtonDownMsg
    //

    class MouseButtonDownMsg final : public AppMsg {
    private:
        MouseButtonMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::mouse_button_down; }
        inline StringRepr to_string() const override { return "MouseButtonDownMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~MouseButtonDownMsg() {}
    private:
        MouseButtonDownMsg(AppMsgArgs*);
    };

    // 
    // MouseButtonUpMsg
    //

    class MouseButtonUpMsg final : public AppMsg {
    private:
        MouseButtonMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::mouse_button_up; }
        inline StringRepr to_string() const override { return "MouseButtonUpMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~MouseButtonUpMsg() {}
    private:
        MouseButtonUpMsg(AppMsgArgs*);
    };

    //
    // MouseMotionMsg
    //
   
    class MouseMotionMsg final : public AppMsg {
    private:
        MouseMotionMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::mouse_motion; }
        inline StringRepr to_string() const override { return "MouseMotionMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~MouseMotionMsg() {}
    private:
        MouseMotionMsg(AppMsgArgs*);
    };

    //
    // MouseWheelMsg
    //

    class MouseWheelMsg final : public AppMsg {
    private:
        MouseWheelMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const { return AppMsg::mouse_wheel; }
        inline StringRepr to_string() const { return "MouseWheenMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~MouseWheelMsg() {}
    private:
        MouseWheelMsg(AppMsgArgs*);
    };

    // 
    // JoyAxisMotionMsg
    //

    class JoyAxisMotionMsg final : public AppMsg {
    private:
        JoyAxisMotionMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::joy_axis_motion; }
        inline StringRepr to_string() const override { return "JoyAxisMotionMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~JoyAxisMotionMsg() {}
    private:
        JoyAxisMotionMsg(AppMsgArgs*);
    };

    //
    // JoyBallMotionMsg
    //

    class JoyBallMotionMsg final : public AppMsg {
    private:
        JoyBallMotionMsgArgs* _args;
    public:
        inline const AppMsgType get_type() const override { return AppMsg::joy_ball_motion; }
        inline StringRepr to_string() const override { return "JoyBallMotionMsg"; }
        static AppMsg* create(AppMsgAccessKey&, AppMsgArgs*);
    protected:
        inline ~JoyBallMotionMsg() {}
    private:
        JoyBallMotionMsg(AppMsgArgs*);
    };


}