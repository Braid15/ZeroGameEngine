#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"

namespace ZeroEngine {

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

    class SystemMsgArgs : public AppMsgArgs {
    public:
        inline SystemMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline StringRepr to_string() const { return "SystemMsgArgs"; }
    };

    class KeyDownMsgArgs : public AppMsgArgs {
    public:
        inline KeyDownMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const { return "KeyDownMsgArgs"; }
    };

    class KeyUpMsgArgs : public AppMsgArgs {
    public:
        inline KeyUpMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const { return "KeyUpMsgArgs"; }
    };
}