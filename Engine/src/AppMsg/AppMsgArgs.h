#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"

namespace ZeroEngine {

    //
    // AppMsgArgs
    //

    class AppMsgArgs {
    private:
        Time _creation_time;
    public:
        virtual ~AppMsgArgs() {}
    public:
        inline virtual StringRepr to_string() const = 0;
        inline Time get_creation_time() const { return _creation_time; }
    protected:
        inline AppMsgArgs(Time time) : _creation_time(time) {}
    };

    //
    // EmptyMsgArgs
    //

    class EmptyMsgArgs : public AppMsgArgs {
    public:
        inline EmptyMsgArgs(Time time) : AppMsgArgs(time) {}
        inline ~EmptyMsgArgs() {}
        inline StringRepr to_string() const { return "EmptyMsgArgs"; }
    };

    //
    // MouseMotionMsgArgs
    //

    class MouseMotionMsgArgs : public AppMsgArgs {
    public:
        inline MouseMotionMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline StringRepr to_string() const { return "MouseMsgArgs"; }
    };

    //
    // WindowMsgArgs
    //

    class WindowMsgArgs : public AppMsgArgs {
    public:
        inline WindowMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline StringRepr to_string() const { return "WindowMsgArgs"; }
    };

    //
    // SystemMsgArgs
    //

    class SystemMsgArgs : public AppMsgArgs {
    public:
        inline SystemMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline StringRepr to_string() const { return "SystemMsgArgs"; }
    };

    //
    // KeyboardMsgArgs
    //

    class KeyboardMsgArgs : public AppMsgArgs {
    public:
        inline KeyboardMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const { return "KeyboardMsgArgs"; }
    };

    //
    // TextEditMsgArgs
    //

    class TextEditMsgArgs : public AppMsgArgs {
    public:
        inline TextEditMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const { return "TextEditMsgArgs"; }
    };

    //
    // TextInputMsgArgs
    //

    class TextInputMsgArgs : public AppMsgArgs {
    public:
        inline TextInputMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const { return "TextInputMsgArgs"; }
    };

    //
    // KeyMapChangedMsgArgs
    //

    class KeyMapChangedMsgArgs : public AppMsgArgs {
    public:
        inline KeyMapChangedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const { return "KeyMapChangedMsgArgs"; }

    };

    //
    // MouseButtonMsgArgs
    //

    class MouseButtonMsgArgs : public AppMsgArgs {
    public:
        inline MouseButtonMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const { return "MouseButtonMsgArgs"; }
    };

    //
    // MouseWheelMsgArgs
    //

    class MouseWheelMsgArgs : public AppMsgArgs {
    public:
        inline MouseWheelMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const { return "MouseWheelMsgArgs"; }
    };

    //
    // JoyAxisMotionMsgArgs
    //

    class JoyAxisMotionMsgArgs : public AppMsgArgs {
    public:
        inline JoyAxisMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const { return "JoyAxisMotionMsgArgs"; }
    };

    //
    // JoyBallMotionMsgArgs
    //

    class JoyBallMotionMsgArgs : public AppMsgArgs {
    public:
        inline JoyBallMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const { return "JoyBallMotionMsgArgs"; }
    };
}