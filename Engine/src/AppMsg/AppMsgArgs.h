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
    // WindowMsgArgs
    //

    // @TODO: Fields are sdl
    class WindowMsgArgs : public AppMsgArgs {
    private:
        uint32_t _window_id;
        uint8_t _event;
        int32_t data1;
        int32_t data2;
    public:
        inline WindowMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline StringRepr to_string() const override { return "WindowMsgArgs"; }
    };

    //
    // SystemMsgArgs
    //

    // This event is for video driver
    // @@TODO: See SDL_events.h line: 520
    class SystemMsgArgs : public AppMsgArgs {
    public:
        inline SystemMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline StringRepr to_string() const override { return "SystemMsgArgs"; }
    };
    
    //
    // KeyboardMsgArgs
    //

    // @TODO: Fields are sdl
    class KeyboardMsgArgs : public AppMsgArgs {
    private:
        uint8_t _state;
        uint8_t _repeat;
        uint32_t _key;
        uint32_t _window;
    public:
        inline KeyboardMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "KeyboardMsgArgs"; }
    };

    //
    // TextEditMsgArgs
    //

    // @TODO: Fields are sdl
    class TextEditMsgArgs : public AppMsgArgs {
    private:
        uint32_t _window;
        char _text[32];
        int32_t _start;
        int32_t _length;
    public:
        inline TextEditMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "TextEditMsgArgs"; }
    };

    //
    // TextInputMsgArgs
    //

    // @TODO: Fields are sdl
    class TextInputMsgArgs : public AppMsgArgs {
    private:
        uint32_t _window;
        char _text[32];
    public:
        inline TextInputMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "TextInputMsgArgs"; }
    };

    //
    // KeyMapChangedMsgArgs
    //

    // @TODO: Fields are sdl
    class KeyMapChangedMsgArgs : public AppMsgArgs {
    private:

    public:
        inline KeyMapChangedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "KeyMapChangedMsgArgs"; }

    };

    //
    // MouseMotionMsgArgs
    //

    // @TODO: Fields are sdl
    class MouseMotionMsgArgs : public AppMsgArgs {
    private:
        uint32_t _window;
        uint32_t _mouse_id;
        uint32_t _button_state;
        int32_t _x;
        int32_t _y;
        int32_t _x_rel;
        int32_t _y_rel;
    public:
        inline MouseMotionMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline StringRepr to_string() const override { return "MouseMsgArgs"; }
    };

    //
    // MouseButtonMsgArgs
    //

    // @TODO: Fields are sdl
    class MouseButtonMsgArgs : public AppMsgArgs {
    private:
        uint32_t _window;
        uint32_t _mouse_id;
        uint8_t _button;
        uint8_t _state;
        uint8_t _clicks;
        int32_t _x;
        int32_t _y;
    public:
        inline MouseButtonMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "MouseButtonMsgArgs"; }
    };

    //
    // MouseWheelMsgArgs
    //

    // @TODO: Fields are sdl
    class MouseWheelMsgArgs : public AppMsgArgs {
    private:
        uint32_t _window;
        uint32_t _mouse_id;
        int32_t _x;
        int32_t _y;
        uint32_t _direction;
    public:
        inline MouseWheelMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "MouseWheelMsgArgs"; }
    };

    //
    // JoyAxisMotionMsgArgs
    //

    // @TODO: Fields are sdl
    class JoyAxisMotionMsgArgs : public AppMsgArgs {
    private:
        // SDL_JoystickID
        uint32_t _joystick_id;
        uint8_t _axis;
        int8_t _value;
    public:
        inline JoyAxisMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "JoyAxisMotionMsgArgs"; }
    };

    //
    // JoyBallMotionMsgArgs
    //

    // @TODO: Fields are sdl
    class JoyBallMotionMsgArgs : public AppMsgArgs {
    private:
        // SDL_JoystickID
        uint32_t _joystick_id;
        uint8_t _ball;
        int16_t _x_rel;
        int16_t _y_rel;
    public:
        inline JoyBallMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "JoyBallMotionMsgArgs"; }
    };

    //
    // JoyHatMotionMsgArgs
    //

    // @TODO: Fields are sdl
    class JoyHatMotionMsgArgs : public AppMsgArgs {
    private:
        // SDL_JoystickID
        uint32_t _joystick_id;
        uint8_t _hat;
        uint8_t _value;
    public:
        inline JoyHatMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "JoyHatMotionMsgArgs"; }
    };

    // 
    // JoyButtonMsgArgs
    //

    // @TODO: Fields are sdl
    class JoyButtonMsgArgs : public AppMsgArgs {
    private:
        // SDL_JoystickID
        uint32_t _joystick_id;
        uint8_t _button;
        uint8_t _state;
    public:
        inline JoyButtonMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "JoyButtonMsgArgs"; }
    };

    //
    // JoyDeviceAddedMsgArgs
    //

    // @TODO: FIelds are sdl
    class JoyDeviceAddedMsgArgs : public AppMsgArgs {
    private:
        int32_t _device_id;
    public:
        inline JoyDeviceAddedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "JoyDeviceAddedMsgArgs"; }
    };

    //
    // JoyDeviceRemovedMsgArgs
    //

    class JoyDeviceRemovedMsgArgs : public AppMsgArgs {
    private:
        int32_t _device_id;
    public:
        inline JoyDeviceRemovedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "JoyDeviceRemovedMsgArgs"; }
    };

    //
    // ControllerAxisMotionMsgArgs
    //

    // @TODO: Fields are sdl
    class ControllerAxisMotionMsgArgs : public AppMsgArgs {
    private:
        // SDL_JoystickID
        uint32_t _which;
        // SDL_GameControllerAxis
        uint8_t _axis;
        int16_t _value;
    public:
        inline ControllerAxisMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "ControllerAxisMotionMsgArgs"; }
    };

    //
    // ControllerButtonMsgArgs
    //

    // @TODO: Fields are sdl
    class ControllerButtonMsgArgs : public AppMsgArgs {
    private:
        // SDL_JoystickID
        uint32_t _which;
        uint8_t _button;
        uint8_t _state;
    public:
        inline ControllerButtonMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "ControllerAxisButtonMsgArgs"; }
    };

    //
    // ControllerDeviceAddedMsgArgs
    //

    // @TODO: Fields are sdl
    class ControllerDeviceAddedMsgArgs : public AppMsgArgs {
    private:
        // SDL_events.h line: 393
        uint32_t _which;
    public:
        inline ControllerDeviceAddedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "ControllerDeviceAddedMsgArgs"; }
    };

    //
    // ControllerDeviceRemovedMsgArgs
    //

    class ControllerDeviceRemovedMsgArgs : public AppMsgArgs {
    private:
        // SDL_events.h line: 393
        uint32_t _which;
    public:
        inline ControllerDeviceRemovedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "ControllerDeviceRemovedMsgArgs"; }
    };

    //
    // ControllerDeviceRemappedMsgArgs
    //

    class ControllerDeviceRemappedMsgArgs : public AppMsgArgs {
    private:
        // SDL_events.h line: 393
        uint32_t _which;
    public:
        inline ControllerDeviceRemappedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "ControllerDeviceRemappedMsgArgs"; }
    };

    // @@REFACTOR: FingerMsgArgs instead of FingerDown and FingerUpMsg args 

    //
    // FingerDownMsgArgs
    //

    // TODO: Fields are sdl
    class FingerDownMsgArgs : public AppMsgArgs {
    private:
        // SDL_TouchID
        uint32_t _touch_id;
        // SDL_FingerID
        uint32_t _finger_id;
        float_t _x;
        float_t _y;
        float_t _delta_x;
        float_t _delta_y;
        float_t _pressure;
    public:
        inline FingerDownMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "FingerDownMsgArgs"; }
    };

    //
    // FingerUpMsgArgs
    //

    class FingerUpMsgArgs : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline FingerUpMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "FingerUpMsgArgs"; }
    };

    //
    // FingerMotionMsgArgs
    //

    class FingerMotionMsgArgs : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
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

    // @@REFACTOR: DropFileMsgArgs for DropBeginMsgArgs, DropTextMsgArgs and DropTextMsgArgs
    // @@TODO: Fields are sdl
    class DropFileMsgArgs : public AppMsgArgs {
    private:
        char* _file;
        uint32_t _window_id;
    public:
        inline DropFileMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "DropFileMsgArgs"; }
    };

    //
    // DropTextMsgArgs
    //

    class DropTextMsgArgs : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline DropTextMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "DropTextMsgArgs"; }
    };

    // 
    // DropBeginMsgArgs
    //

    class DropBeginMsgArgs : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline DropBeginMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "DropBeginMsgArgs"; }
    };

    //
    // DropCompleteMsgArgs
    //

    class DropCompleteMsgArgs : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline DropCompleteMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "DropCompleteMsgArgs"; }
    };

    //
    // AudioDeviceAddedMsgArgs
    //

    // @@REFACTOR: AudioDeviceMsgArgs for AudioDeviceAddedMsg and AudioDeviceRemovedMsg
    // @TODO: Fields are sdl
    class AudioDeviceAddedMsgArgs : public AppMsgArgs {
    private:
        // SDL_events.hj line: 407
        uint32_t _which;
        uint8_t _is_captured;
    public:
        inline AudioDeviceAddedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline StringRepr to_string() const override { return "AudioDeviceAddedMsgArgs"; }
    };

    //
    // AudioDeviceRemovedMsgArgs
    //

    class AudioDeviceRemovedMsgArgs : public AppMsgArgs {
    // @@TODO: See above REFACTOR
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