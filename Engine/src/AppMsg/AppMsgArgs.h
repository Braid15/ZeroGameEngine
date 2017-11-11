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
        inline StringRepr to_string() const override { return "EmptyMsgArgs"; }
    };

    //
    // MouseMotionMsgArgs
    //

    class MouseMotionMsgArgs : public AppMsgArgs {
    public:
        inline MouseMotionMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline StringRepr to_string() const override { return "MouseMsgArgs"; }
    };

    //
    // WindowMsgArgs
    //

    class WindowMsgArgs : public AppMsgArgs {
    public:
        inline WindowMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline StringRepr to_string() const override { return "WindowMsgArgs"; }
    };

    //
    // SystemMsgArgs
    //

    class SystemMsgArgs : public AppMsgArgs {
    public:
        inline SystemMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline StringRepr to_string() const override { return "SystemMsgArgs"; }
    };

    //
    // KeyboardMsgArgs
    //

    class KeyboardMsgArgs : public AppMsgArgs {
    public:
        inline KeyboardMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "KeyboardMsgArgs"; }
    };

    //
    // TextEditMsgArgs
    //

    class TextEditMsgArgs : public AppMsgArgs {
    public:
        inline TextEditMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "TextEditMsgArgs"; }
    };

    //
    // TextInputMsgArgs
    //

    class TextInputMsgArgs : public AppMsgArgs {
    public:
        inline TextInputMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "TextInputMsgArgs"; }
    };

    //
    // KeyMapChangedMsgArgs
    //

    class KeyMapChangedMsgArgs : public AppMsgArgs {
    public:
        inline KeyMapChangedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "KeyMapChangedMsgArgs"; }

    };

    //
    // MouseButtonMsgArgs
    //

    class MouseButtonMsgArgs : public AppMsgArgs {
    public:
        inline MouseButtonMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "MouseButtonMsgArgs"; }
    };

    //
    // MouseWheelMsgArgs
    //

    class MouseWheelMsgArgs : public AppMsgArgs {
    public:
        inline MouseWheelMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "MouseWheelMsgArgs"; }
    };

    //
    // JoyAxisMotionMsgArgs
    //

    class JoyAxisMotionMsgArgs : public AppMsgArgs {
    public:
        inline JoyAxisMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "JoyAxisMotionMsgArgs"; }
    };

    //
    // JoyBallMotionMsgArgs
    //

    class JoyBallMotionMsgArgs : public AppMsgArgs {
    public:
        inline JoyBallMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "JoyBallMotionMsgArgs"; }
    };

    //
    // JoyHatMotionMsgArgs
    //

    class JoyHatMotionMsgArgs : public AppMsgArgs {
    public:
        inline JoyHatMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "JoyHatMotionMsgArgs"; }
    };

    // 
    // JoyButtonMsgArgs
    //

    class JoyButtonMsgArgs : public AppMsgArgs {
    public:
        inline JoyButtonMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "JoyButtonMsgArgs"; }
    };

    //
    // JoyDeviceAddedMsgArgs
    //

    class JoyDeviceAddedMsgArgs : public AppMsgArgs {
    public:
        inline JoyDeviceAddedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "JoyDeviceAddedMsgArgs"; }
    };

    //
    // JoyDeviceRemovedMsgArgs
    //

    class JoyDeviceRemovedMsgArgs : public AppMsgArgs {
    public:
        inline JoyDeviceRemovedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "JoyDeviceRemovedMsgArgs"; }
    };

    //
    // ControllerAxisMotionMsgArgs
    //

    class ControllerAxisMotionMsgArgs : public AppMsgArgs {
    public:
        inline ControllerAxisMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "ControllerAxisMotionMsgArgs"; }
    };

    //
    // ControllerAxisButtonMsgArgs
    //

    class ControllerButtonMsgArgs : public AppMsgArgs {
    public:
        inline ControllerButtonMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "ControllerAxisButtonMsgArgs"; }
    };

    //
    // ControllerDeviceAddedMsgArgs
    //

    class ControllerDeviceAddedMsgArgs : public AppMsgArgs {
    public:
        inline ControllerDeviceAddedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "ControllerDeviceAddedMsgArgs"; }
    };

    //
    // ControllerDeviceRemovedMsgArgs
    //

    class ControllerDeviceRemovedMsgArgs : public AppMsgArgs {
    public:
        inline ControllerDeviceRemovedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "ControllerDeviceRemovedMsgArgs"; }
    };

    //
    // ControllerDeviceRemappedMsgArgs
    //

    class ControllerDeviceRemappedMsgArgs : public AppMsgArgs {
    public:
        inline ControllerDeviceRemappedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "ControllerDeviceRemappedMsgArgs"; }
    };

    // @@TODO: Can probably put FingerDownMsgArgs and FingerUpMsgArgs into one class

    //
    // FingerDownMsgArgs
    //

    class FingerDownMsgArgs : public AppMsgArgs {
    public:
        inline FingerDownMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "FingerDownMsgArgs"; }
    };

    //
    // FingerUpMsgArgs
    //

    class FingerUpMsgArgs : public AppMsgArgs {
    public:
        inline FingerUpMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "FingerUpMsgArgs"; }
    };

    //
    // FingerMotionMsgArgs
    //

    class FingerMotionMsgArgs : public AppMsgArgs {
        inline FingerMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "FingerMotionMsgArgs"; }
    };

    //
    // ClipboardMsgArgs
    //

    class ClipboardMsgArgs : public AppMsgArgs {
    public:
        inline ClipboardMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "ClipboardMsgArgs"; }
    };

    //
    // DropFileMsgArgs
    //

    class DropFileMsgArgs : public AppMsgArgs {
    public:
        inline DropFileMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "DropFileMsgArgs"; }
    };

    //
    // DropTextMsgArgs
    //

    class DropTextMsgArgs : public AppMsgArgs {
    public:
        inline DropTextMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "DropTextMsgArgs"; }
    };

    // 
    // DropBeginMsgArgs
    //

    class DropBeginMsgArgs : public AppMsgArgs {
    public:
        inline DropBeginMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "DropBeginMsgArgs"; }
    };

    //
    // DropCompleteMsgArgs
    //

    class DropCompleteMsgArgs : public AppMsgArgs {
    public:
        inline DropCompleteMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "DropCompleteMsgArgs"; }
    };

    //
    // AudioDeviceAddedMsgArgs
    //

    class AudioDeviceAddedMsgArgs : public AppMsgArgs {
    public:
        inline AudioDeviceAddedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "AudioDeviceAddedMsgArgs"; }
    };

    //
    // AudioDeviceRemovedMsgArgs
    //

    class AudioDeviceRemovedMsgArgs : public AppMsgArgs {
    public:
        inline AudioDeviceRemovedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "AudioDeviceRemovedMsgArgs"; }
    };

    //
    // RenderTargetsResetMsgArgs
    //

    class RenderTargetsResetMsgArgs : public AppMsgArgs {
    public:
        inline RenderTargetsResetMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "RenderTargetsResetMsgArgs"; }
    };

    //
    // RenderDeviceResetMsgArgs
    //

    class RenderDeviceResetMsgArgs : public AppMsgArgs {
    public:
        inline RenderDeviceResetMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "RenderDeviceResetMsgArgs"; }
    };
}