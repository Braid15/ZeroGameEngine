#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Graphics/Point.h"
#include "../Input/Keys.h"

namespace ZeroEngine {

    // @TODO: MsgArgs should be using MemoryPool 

    // @TODO: Put this in different file?
    enum class ButtonState : char {
        null = -1,
        begin = 1,
        released = 1,
        pressed,
        end
    };


    //
    // AppMsgArgs
    //

    class AppMsgArgs : public IZeroObject {
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

    class EmptyMsgArgs final : public AppMsgArgs {
    public:
        inline EmptyMsgArgs(Time time) : AppMsgArgs(time) {}
        inline ~EmptyMsgArgs() {}
        inline StringRepr to_string() const override { return "EmptyMsgArgs"; }
    };

    //
    // WindowMsgArgs
    //

    // @TODO: Fields are sdl
    class WindowMsgArgs final : public AppMsgArgs {
    private:
        uint32_t _window_id;
        uint8_t _event;
        int32_t data1;
        int32_t data2;
    public:
        inline WindowMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline ~WindowMsgArgs() {}
        inline StringRepr to_string() const override { return "WindowMsgArgs"; }
    };

    //
    // SystemMsgArgs
    //

    // This event is for video driver
    // @@TODO: See SDL_events.h line: 520
    class SystemMsgArgs final : public AppMsgArgs {
    public:
        inline SystemMsgArgs(Time create_time) : AppMsgArgs(create_time) {}
        inline ~SystemMsgArgs() {}
        inline StringRepr to_string() const override { return "SystemMsgArgs"; }
    };
    
    //
    // KeyboardMsgArgs
    //

    class KeyboardMsgArgs final : public AppMsgArgs {
    private:
        KeyState _state;
        bool _is_repeat;
        Key _key;
        uint32_t _window;
    public:
        KeyboardMsgArgs(Time time_stamp, uint32_t window, Key& key, bool repeat, KeyState state);
        inline ~KeyboardMsgArgs() {}
        inline KeyState get_key_state() const { return _state; }
        inline bool is_repeat() const { return _is_repeat; }
        inline Key get_key() const { return _key; }
        inline uint32_t get_window() const { return _window; }
        inline StringRepr to_string() const override { return "KeyboardMsgArgs"; }
    };

    //
    // TextEditMsgArgs
    //

    // @TODO: Fields are sdl
    class TextEditMsgArgs final : public AppMsgArgs {
    private:
        uint32_t _window;
        char _text[32];
        int32_t _start;
        int32_t _length;
    public:
        inline TextEditMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~TextEditMsgArgs() {}
        inline StringRepr to_string() const override { return "TextEditMsgArgs"; }
    };

    //
    // TextInputMsgArgs
    //

    // @TODO: Fields are sdl
    class TextInputMsgArgs final : public AppMsgArgs {
    private:
        uint32_t _window;
        char _text[32];
    public:
        inline TextInputMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~TextInputMsgArgs() {}
        inline StringRepr to_string() const override { return "TextInputMsgArgs"; }
    };

    //
    // KeyMapChangedMsgArgs
    //

    // @TODO: Fields are sdl
    class KeyMapChangedMsgArgs final : public AppMsgArgs {
    private:

    public:
        inline KeyMapChangedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~KeyMapChangedMsgArgs() {}
        inline StringRepr to_string() const override { return "KeyMapChangedMsgArgs"; }

    };

    //
    // MouseMotionMsgArgs
    //

    enum class MouseButton : int8_t {
        null = -1,
        begin = 1,
        left = 1,
        middle,
        right,
        four,
        five,
        end,
    };

    class MouseMotionMsgArgs final : public AppMsgArgs {
    private:
        uint32_t _window;
        uint32_t _mouse_id;
        ButtonState _buttons[static_cast<int>(MouseButton::end)];
        Point<int32_t> _x_y_coordinates;
        Point<int32_t> _x_y_relative;
    public:
        MouseMotionMsgArgs(Time time_stamp, uint32_t window, uint32_t mouse, 
                           ButtonState buttons[static_cast<int>(MouseButton::end)], int32_t x_pos,
                           int32_t y_pos, int32_t x_rel, int32_t y_rel);
        inline ~MouseMotionMsgArgs() {}
        inline StringRepr to_string() const override { return "MouseMsgArgs"; }
        inline uint32_t get_window() const { return _window; }
        inline uint32_t get_mouse_id() const { return _mouse_id; }
        inline int32_t get_x_pos() const { return _x_y_coordinates.get_x(); }
        inline int32_t get_y_pos() const { return _x_y_coordinates.get_y(); }
        inline Point<int32_t> get_coordinates() const { return _x_y_coordinates; }
        inline int32_t get_x_rel() const { return _x_y_relative.get_x(); }
        inline int32_t get_y_rel() const { return _x_y_relative.get_y(); }
        inline Point<int32_t> get_rel_coordinates() const { return _x_y_relative; }
        bool is_pressed(MouseButton) const;


    };

    //
    // MouseButtonMsgArgs
    //

    class MouseButtonMsgArgs final : public AppMsgArgs {
    private:
        uint32_t _window;
        uint32_t _mouse_id;
        ButtonState _state;
        uint8_t _clicks;
        MouseButton _button;
        Point<int32_t> _x_y_coordinates;
    public:
        MouseButtonMsgArgs(Time time_stamp, uint32_t window, uint32_t mouse_id, ButtonState state,
                           uint8_t num_clicks, MouseButton button, int32_t x_pos, int32_t y_pos);
        inline MouseButtonMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~MouseButtonMsgArgs() {}
        inline StringRepr to_string() const override { return "MouseButtonMsgArgs"; }
        inline uint8_t get_num_clicks() const { return _clicks; }
        inline int32_t get_x_pos() const { return _x_y_coordinates.get_x(); }
        inline int32_t get_y_pos() const { return _x_y_coordinates.get_y(); }
        inline Point<int32_t> get_coordinates() const { return _x_y_coordinates; }
        inline MouseButton get_button() const { return _button; }
        inline ButtonState get_state() const { return _state; }
    };

    //
    // MouseWheelMsgArgs
    //

    // @TODO: Fields are sdl
    class MouseWheelMsgArgs final : public AppMsgArgs {
    private:
        uint32_t _window;
        uint32_t _mouse_id;
        Point<int32_t> _x_y_coordinates;
        uint32_t _direction;
    public:
        inline MouseWheelMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~MouseWheelMsgArgs() {}
        inline StringRepr to_string() const override { return "MouseWheelMsgArgs"; }
    };

    //
    // JoyAxisMotionMsgArgs
    //

    // @TODO: Fields are sdl
    class JoyAxisMotionMsgArgs final : public AppMsgArgs {
    private:
        // SDL_JoystickID
        uint32_t _joystick_id;
        uint8_t _axis;
        int8_t _value;
    public:
        inline JoyAxisMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~JoyAxisMotionMsgArgs() {}
        inline StringRepr to_string() const override { return "JoyAxisMotionMsgArgs"; }
    };

    //
    // JoyBallMotionMsgArgs
    //

    // @TODO: Fields are sdl
    class JoyBallMotionMsgArgs final : public AppMsgArgs {
    private:
        // SDL_JoystickID
        uint32_t _joystick_id;
        uint8_t _ball;
        int16_t _x_rel;
        int16_t _y_rel;
    public:
        inline JoyBallMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~JoyBallMotionMsgArgs() {}
        inline StringRepr to_string() const override { return "JoyBallMotionMsgArgs"; }
    };

    //
    // JoyHatMotionMsgArgs
    //

    // @TODO: Fields are sdl
    class JoyHatMotionMsgArgs final : public AppMsgArgs {
    private:
        // SDL_JoystickID
        uint32_t _joystick_id;
        uint8_t _hat;
        uint8_t _value;
    public:
        inline JoyHatMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~JoyHatMotionMsgArgs() {}
        inline StringRepr to_string() const override { return "JoyHatMotionMsgArgs"; }
    };

    // 
    // JoyButtonMsgArgs
    //

    // @TODO: Fields are sdl
    class JoyButtonMsgArgs final : public AppMsgArgs {
    private:
        // SDL_JoystickID
        uint32_t _joystick_id;
        uint8_t _button;
        uint8_t _state;
    public:
        inline JoyButtonMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~JoyButtonMsgArgs() {}
        inline StringRepr to_string() const override { return "JoyButtonMsgArgs"; }
    };

    //
    // JoyDeviceAddedMsgArgs
    //

    // @TODO: FIelds are sdl
    class JoyDeviceAddedMsgArgs final : public AppMsgArgs {
    private:
        int32_t _device_id;
    public:
        inline JoyDeviceAddedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~JoyDeviceAddedMsgArgs() {}
        inline StringRepr to_string() const override { return "JoyDeviceAddedMsgArgs"; }
    };

    //
    // JoyDeviceRemovedMsgArgs
    //

    class JoyDeviceRemovedMsgArgs final : public AppMsgArgs {
    private:
        int32_t _device_id;
    public:
        inline JoyDeviceRemovedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~JoyDeviceRemovedMsgArgs() {}
        inline StringRepr to_string() const override { return "JoyDeviceRemovedMsgArgs"; }
    };

    //
    // ControllerAxisMotionMsgArgs
    //

    // @TODO: Fields are sdl
    class ControllerAxisMotionMsgArgs final : public AppMsgArgs {
    private:
        // SDL_JoystickID
        uint32_t _which;
        // SDL_GameControllerAxis
        uint8_t _axis;
        int16_t _value;
    public:
        inline ControllerAxisMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~ControllerAxisMotionMsgArgs() {}
        inline StringRepr to_string() const override { return "ControllerAxisMotionMsgArgs"; }
    };

    //
    // ControllerButtonMsgArgs
    //

    // @TODO: Fields are sdl
    class ControllerButtonMsgArgs final : public AppMsgArgs {
    private:
        // SDL_JoystickID
        uint32_t _which;
        uint8_t _button;
        uint8_t _state;
    public:
        inline ControllerButtonMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~ControllerButtonMsgArgs() {}
        inline StringRepr to_string() const override { return "ControllerAxisButtonMsgArgs"; }
    };

    //
    // ControllerDeviceAddedMsgArgs
    //

    // @TODO: Fields are sdl
    class ControllerDeviceAddedMsgArgs final : public AppMsgArgs {
    private:
        // SDL_events.h line: 393
        uint32_t _which;
    public:
        inline ControllerDeviceAddedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~ControllerDeviceAddedMsgArgs() {}
        inline StringRepr to_string() const override { return "ControllerDeviceAddedMsgArgs"; }
    };

    //
    // ControllerDeviceRemovedMsgArgs
    //

    class ControllerDeviceRemovedMsgArgs final : public AppMsgArgs {
    private:
        // SDL_events.h line: 393
        uint32_t _which;
    public:
        inline ControllerDeviceRemovedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~ControllerDeviceRemovedMsgArgs() {}
        inline StringRepr to_string() const override { return "ControllerDeviceRemovedMsgArgs"; }
    };

    //
    // ControllerDeviceRemappedMsgArgs
    //

    class ControllerDeviceRemappedMsgArgs final : public AppMsgArgs {
    private:
        // SDL_events.h line: 393
        uint32_t _which;
    public:
        inline ControllerDeviceRemappedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~ControllerDeviceRemappedMsgArgs() {}
        inline StringRepr to_string() const override { return "ControllerDeviceRemappedMsgArgs"; }
    };

    // @@REFACTOR: FingerMsgArgs instead of FingerDown and FingerUpMsg args 

    //
    // FingerDownMsgArgs
    //

    // TODO: Fields are sdl
    class FingerDownMsgArgs final : public AppMsgArgs {
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
        inline ~FingerDownMsgArgs() {}
        inline StringRepr to_string() const override { return "FingerDownMsgArgs"; }
    };

    //
    // FingerUpMsgArgs
    //

    class FingerUpMsgArgs final : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline FingerUpMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~FingerUpMsgArgs() {}
        inline StringRepr to_string() const override { return "FingerUpMsgArgs"; }
    };

    //
    // FingerMotionMsgArgs
    //

    class FingerMotionMsgArgs final : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline FingerMotionMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~FingerMotionMsgArgs() {}
        inline StringRepr to_string() const override { return "FingerMotionMsgArgs"; }
    };

    //
    // ClipboardMsgArgs
    //

    class ClipboardMsgArgs final : public AppMsgArgs {
    public:
        inline ClipboardMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~ClipboardMsgArgs() {}
        inline StringRepr to_string() const override { return "ClipboardMsgArgs"; }
    };

    //
    // DropFileMsgArgs
    //

    // @@REFACTOR: DropFileMsgArgs for DropBeginMsgArgs, DropTextMsgArgs and DropTextMsgArgs
    // @@TODO: Fields are sdl
    class DropFileMsgArgs final : public AppMsgArgs {
    private:
        char* _file;
        uint32_t _window_id;
    public:
        inline DropFileMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~DropFileMsgArgs() {}
        inline StringRepr to_string() const override { return "DropFileMsgArgs"; }
    };

    //
    // DropTextMsgArgs
    //

    class DropTextMsgArgs final : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline DropTextMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~DropTextMsgArgs() {}
        inline StringRepr to_string() const override { return "DropTextMsgArgs"; }
    };

    // 
    // DropBeginMsgArgs
    //

    class DropBeginMsgArgs final : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline DropBeginMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~DropBeginMsgArgs() {}
        inline StringRepr to_string() const override { return "DropBeginMsgArgs"; }
    };

    //
    // DropCompleteMsgArgs
    //

    class DropCompleteMsgArgs final : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline DropCompleteMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~DropCompleteMsgArgs() {}
        inline StringRepr to_string() const override { return "DropCompleteMsgArgs"; }
    };

    //
    // AudioDeviceAddedMsgArgs
    //

    // @@REFACTOR: AudioDeviceMsgArgs for AudioDeviceAddedMsg and AudioDeviceRemovedMsg
    // @TODO: Fields are sdl
    class AudioDeviceAddedMsgArgs final : public AppMsgArgs {
    private:
        // SDL_events.hj line: 407
        uint32_t _which;
        uint8_t _is_captured;
    public:
        inline AudioDeviceAddedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~AudioDeviceAddedMsgArgs() {}
        inline StringRepr to_string() const override { return "AudioDeviceAddedMsgArgs"; }
    };

    //
    // AudioDeviceRemovedMsgArgs
    //

    class AudioDeviceRemovedMsgArgs final : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline AudioDeviceRemovedMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~AudioDeviceRemovedMsgArgs() {}
        inline StringRepr to_string() const override { return "AudioDeviceRemovedMsgArgs"; }
    };

    //
    // RenderTargetsResetMsgArgs
    //

    class RenderTargetsResetMsgArgs final : public AppMsgArgs {
    public:
        inline RenderTargetsResetMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~RenderTargetsResetMsgArgs() {}
        inline StringRepr to_string() const override { return "RenderTargetsResetMsgArgs"; }
    };

    //
    // RenderDeviceResetMsgArgs
    //

    class RenderDeviceResetMsgArgs final : public AppMsgArgs {
    public:
        inline RenderDeviceResetMsgArgs(Time time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~RenderDeviceResetMsgArgs() {}
        inline StringRepr to_string() const override { return "RenderDeviceResetMsgArgs"; }
    };
}