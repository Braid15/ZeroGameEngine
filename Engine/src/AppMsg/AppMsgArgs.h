#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Graphics/Point.h"
#include "../Input/Keys.h"

namespace ZeroEngine {

    // @TODO: MsgArgs should be using MemoryPool 

    // @TODO: Put this in different file?
    enum class ButtonState : Int8 {
        null = -1,
        begin = 1,
        released = 1,
        pressed,
        end
    };

    inline std::ostream& operator<<(std::ostream& os, ButtonState state) {
        if (state == ButtonState::null) {
            os << "ButtonState::null";
        } else if (state == ButtonState::begin) {
            os << "ButtonState::begin";
        } else if (state == ButtonState::released) {
            os << "ButtonState::released";
        } else if (state == ButtonState::pressed) {
            os << "ButtonState::pressed";
        } else if (state == ButtonState::end) {
            os << "ButtonState::end";
        } else {
            os.setstate(std::ios_base::failbit);
        }
        return os;
    }


    //
    // AppMsgArgs
    //

    class AppMsgArgs : public IZeroObject {
    private:
        Tick _creation_time;
    public:
        virtual ~AppMsgArgs() {}
    public:
        inline virtual StringRepr to_string() const = 0;
        inline Tick get_creation_time() const { return _creation_time; }
    protected:
        inline AppMsgArgs(Tick time) : _creation_time(time) {}
    };

    //
    // EmptyMsgArgs
    //

    class EmptyMsgArgs final : public AppMsgArgs {
    public:
        inline EmptyMsgArgs(Tick time) : AppMsgArgs(time) {}
        inline ~EmptyMsgArgs() {}
        inline StringRepr to_string() const override { return "EmptyMsgArgs"; }
    };

    //
    // WindowMsgArgs
    //

    // @TODO: Fields are sdl
    class WindowMsgArgs final : public AppMsgArgs {
    private:
        Uint32 _window_id;
        Uint8 _event;
        Int32 data1;
        Int32 data2;
    public:
        inline WindowMsgArgs(Tick create_time) : AppMsgArgs(create_time) {}
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
        inline SystemMsgArgs(Tick create_time) : AppMsgArgs(create_time) {}
        inline ~SystemMsgArgs() {}
        inline StringRepr to_string() const override { return "SystemMsgArgs"; }
    };
    
    //
    // KeyboardMsgArgs
    //


    class KeyboardMsgArgs final : public AppMsgArgs {
    private:
        bool _is_repeat;
        KeyState _key_state;
        KeyModStateArray _keymod_states;
        Key _key;
        Uint32 _window;
    public:
        KeyboardMsgArgs(Tick time_stamp, Uint32 window, Key& key, bool repeat, KeyState state,
                        KeyModStateArray mods);
        inline ~KeyboardMsgArgs() {}
        inline bool is_repeat() const { return _is_repeat; }
        inline bool is_pressed() const { return _key_state == KeyState::pressed; }
        inline const KeyState& get_key_state() const { return _key_state; }
        inline const KeyModStateArray& get_keymod_states() const { return _keymod_states; }
        inline Key get_key() const { return _key; }
        inline Uint32 get_window() const { return _window; }
        inline StringRepr to_string() const override { return "KeyboardMsgArgs"; }
    };

    //
    // TextEditMsgArgs
    //

    // @TODO: Fields are sdl
    class TextEditMsgArgs final : public AppMsgArgs {
    private:
        Uint32 _window;
        char _text[32];
        Int32 _start;
        Int32 _length;
    public:
        inline TextEditMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~TextEditMsgArgs() {}
        inline StringRepr to_string() const override { return "TextEditMsgArgs"; }
    };

    //
    // TextInputMsgArgs
    //

    // @TODO: Fields are sdl
    class TextInputMsgArgs final : public AppMsgArgs {
    private:
        Uint32 _window;
        char _text[32];
    public:
        inline TextInputMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
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
        inline KeyMapChangedMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~KeyMapChangedMsgArgs() {}
        inline StringRepr to_string() const override { return "KeyMapChangedMsgArgs"; }

    };

    //
    // MouseMotionMsgArgs
    //

    // @@TODO: This, ButtonState, and MouseWheelDirection need to be in seperate file
    enum class MouseButton : Int8 {
        null = -1,
        begin = 1,
        left = 1,
        middle,
        right,
        four,
        five,
        end,
    };

    inline std::ostream& operator<<(std::ostream& os, MouseButton button) {
        if (button == MouseButton::null) {
            os << "MouseButton::null";
        } else if (button == MouseButton::left) {
            os << "MouseButton::left";
        } else if (button == MouseButton::middle) {
            os << "MouseButton::middle";
        } else if (button == MouseButton::right) {
            os << "MouseButton::right";
        } else if (button == MouseButton::four) {
            os << "MouseButton::four";
        } else if (button == MouseButton::five) {
            os << "MouseButton::five";
        } else if (button == MouseButton::end) {
            os << "MouseButton::end";
        } else {
            os.setstate(std::ios_base::failbit);
        }
        return os;
    }

    typedef std::array<ButtonState, static_cast<Int32>(MouseButton::end)> MouseButtonStateArray;

    class MouseMotionMsgArgs final : public AppMsgArgs {
    private:
        Uint32 _window;
        Uint32 _mouse_id;
        MouseButtonStateArray _button_states;
        Point<Int32> _x_y_coordinates;
        Point<Int32> _x_y_relative;
    public:
        MouseMotionMsgArgs(Tick time_stamp, Uint32 window, Uint32 mouse, 
                           MouseButtonStateArray buttons, Int32 x_pos,
                           Int32 y_pos, Int32 x_rel, Int32 y_rel);
        inline ~MouseMotionMsgArgs() {}
        inline StringRepr to_string() const override { return "MouseMsgArgs"; }
        inline Uint32 get_window() const { return _window; }
        inline Uint32 get_mouse_id() const { return _mouse_id; }
        inline Int32 get_x_pos() const { return _x_y_coordinates.get_x(); }
        inline Int32 get_y_pos() const { return _x_y_coordinates.get_y(); }
        inline Point<Int32> get_coordinates() const { return _x_y_coordinates; }
        inline Int32 get_x_rel() const { return _x_y_relative.get_x(); }
        inline Int32 get_y_rel() const { return _x_y_relative.get_y(); }
        inline Point<Int32> get_rel_coordinates() const { return _x_y_relative; }
        inline MouseButtonStateArray get_button_states() const { return _button_states; }
        bool is_pressed(MouseButton) const;
    };

    //
    // MouseButtonMsgArgs
    //

    class MouseButtonMsgArgs final : public AppMsgArgs {
    private:
        Uint32 _window;
        Uint32 _mouse_id;
        ButtonState _state;
        Uint8 _clicks;
        MouseButton _button;
        Point<Int32> _x_y_coordinates;
    public:
        MouseButtonMsgArgs(Tick time_stamp, Uint32 window, Uint32 mouse_id, ButtonState state,
                           Uint8 num_clicks, MouseButton button, Int32 x_pos, Int32 y_pos);
        inline MouseButtonMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~MouseButtonMsgArgs() {}
        inline StringRepr to_string() const override { return "MouseButtonMsgArgs"; }
        inline Uint8 get_num_clicks() const { return _clicks; }
        inline Int32 get_x_pos() const { return _x_y_coordinates.get_x(); }
        inline Int32 get_y_pos() const { return _x_y_coordinates.get_y(); }
        inline Point<Int32> get_coordinates() const { return _x_y_coordinates; }
        inline MouseButton get_button() const { return _button; }
        inline ButtonState get_state() const { return _state; }
    };

    //
    // MouseWheelMsgArgs
    //

    // @TODO: Different file?
    enum class MouseWheelDirection : char {
        null = -2,
        down = -1,
        up = 1,
    };

    inline std::ostream& operator<<(std::ostream& os, MouseWheelDirection direction) {
        if (direction == MouseWheelDirection::null) {
            os << "MouseWheelDirection::null";
        } else if (direction == MouseWheelDirection::down) {
            os << "MouseWheelDirection::down";
        } else if (direction == MouseWheelDirection::up) {
            os << "MouseWheelDirection::up";
        } else {
            os.setstate(std::ios_base::failbit);
        }
        return os;
    }

    class MouseWheelMsgArgs final : public AppMsgArgs {
    private:
        Uint32 _window;
        Uint32 _mouse_id;
        Point<Int32> _x_y_coordinates;
        MouseWheelDirection _direction;
    public:
        MouseWheelMsgArgs(Tick time_stamp, Uint32 window, Uint32 mouse,
                                 Int32 x, Int32 y, MouseWheelDirection dir);
        inline ~MouseWheelMsgArgs() {}
        inline StringRepr to_string() const override { return "MouseWheelMsgArgs"; }
        inline Uint32 get_window() const { return _window; }
        inline Uint32 get_mouse() const { return _mouse_id; }
        inline Int32 get_scroll_amount_x() const { return _x_y_coordinates.get_x(); }
        inline Int32 get_scroll_amount_y() const { return _x_y_coordinates.get_y(); }
        inline MouseWheelDirection get_direction() const { return _direction; }
    };

    //
    // JoyAxisMotionMsgArgs
    //

    // @TODO: Fields are sdl
    class JoyAxisMotionMsgArgs final : public AppMsgArgs {
    private:
        // SDL_JoystickID
        Uint32 _joystick_id;
        Uint8 _axis;
        Int8 _value;
    public:
        inline JoyAxisMotionMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
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
        Uint32 _joystick_id;
        Uint8 _ball;
        Int16 _x_rel;
        Int16 _y_rel;
    public:
        inline JoyBallMotionMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
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
        Uint32 _joystick_id;
        Uint8 _hat;
        Uint8 _value;
    public:
        inline JoyHatMotionMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
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
        Uint32 _joystick_id;
        Uint8 _button;
        Uint8 _state;
    public:
        inline JoyButtonMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~JoyButtonMsgArgs() {}
        inline StringRepr to_string() const override { return "JoyButtonMsgArgs"; }
    };

    //
    // JoyDeviceAddedMsgArgs
    //

    // @TODO: FIelds are sdl
    class JoyDeviceAddedMsgArgs final : public AppMsgArgs {
    private:
        Int32 _device_id;
    public:
        inline JoyDeviceAddedMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~JoyDeviceAddedMsgArgs() {}
        inline StringRepr to_string() const override { return "JoyDeviceAddedMsgArgs"; }
    };

    //
    // JoyDeviceRemovedMsgArgs
    //

    class JoyDeviceRemovedMsgArgs final : public AppMsgArgs {
    private:
        Int32 _device_id;
    public:
        inline JoyDeviceRemovedMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
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
        Uint32 _which;
        // SDL_GameControllerAxis
        Uint8 _axis;
        Int16 _value;
    public:
        inline ControllerAxisMotionMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
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
        Uint32 _which;
        Uint8 _button;
        Uint8 _state;
    public:
        inline ControllerButtonMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
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
        Uint32 _which;
    public:
        inline ControllerDeviceAddedMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~ControllerDeviceAddedMsgArgs() {}
        inline StringRepr to_string() const override { return "ControllerDeviceAddedMsgArgs"; }
    };

    //
    // ControllerDeviceRemovedMsgArgs
    //

    class ControllerDeviceRemovedMsgArgs final : public AppMsgArgs {
    private:
        // SDL_events.h line: 393
        Uint32 _which;
    public:
        inline ControllerDeviceRemovedMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~ControllerDeviceRemovedMsgArgs() {}
        inline StringRepr to_string() const override { return "ControllerDeviceRemovedMsgArgs"; }
    };

    //
    // ControllerDeviceRemappedMsgArgs
    //

    class ControllerDeviceRemappedMsgArgs final : public AppMsgArgs {
    private:
        // SDL_events.h line: 393
        Uint32 _which;
    public:
        inline ControllerDeviceRemappedMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
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
        Uint32 _touch_id;
        // SDL_FingerID
        Uint32 _finger_id;
        Float32 _x;
        Float32 _y;
        Float32 _delta_x;
        Float32 _delta_y;
        Float32 _pressure;
    public:
        inline FingerDownMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~FingerDownMsgArgs() {}
        inline StringRepr to_string() const override { return "FingerDownMsgArgs"; }
    };

    //
    // FingerUpMsgArgs
    //

    class FingerUpMsgArgs final : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline FingerUpMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~FingerUpMsgArgs() {}
        inline StringRepr to_string() const override { return "FingerUpMsgArgs"; }
    };

    //
    // FingerMotionMsgArgs
    //

    class FingerMotionMsgArgs final : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline FingerMotionMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~FingerMotionMsgArgs() {}
        inline StringRepr to_string() const override { return "FingerMotionMsgArgs"; }
    };

    //
    // ClipboardMsgArgs
    //

    class ClipboardMsgArgs final : public AppMsgArgs {
    public:
        inline ClipboardMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
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
        Uint32 _window_id;
    public:
        inline DropFileMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~DropFileMsgArgs() {}
        inline StringRepr to_string() const override { return "DropFileMsgArgs"; }
    };

    //
    // DropTextMsgArgs
    //

    class DropTextMsgArgs final : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline DropTextMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~DropTextMsgArgs() {}
        inline StringRepr to_string() const override { return "DropTextMsgArgs"; }
    };

    // 
    // DropBeginMsgArgs
    //

    class DropBeginMsgArgs final : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline DropBeginMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~DropBeginMsgArgs() {}
        inline StringRepr to_string() const override { return "DropBeginMsgArgs"; }
    };

    //
    // DropCompleteMsgArgs
    //

    class DropCompleteMsgArgs final : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline DropCompleteMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
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
        Uint32 _which;
        Uint8 _is_captured;
    public:
        inline AudioDeviceAddedMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~AudioDeviceAddedMsgArgs() {}
        inline StringRepr to_string() const override { return "AudioDeviceAddedMsgArgs"; }
    };

    //
    // AudioDeviceRemovedMsgArgs
    //

    class AudioDeviceRemovedMsgArgs final : public AppMsgArgs {
    // @@TODO: See above REFACTOR
    public:
        inline AudioDeviceRemovedMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~AudioDeviceRemovedMsgArgs() {}
        inline StringRepr to_string() const override { return "AudioDeviceRemovedMsgArgs"; }
    };

    //
    // RenderTargetsResetMsgArgs
    //

    class RenderTargetsResetMsgArgs final : public AppMsgArgs {
    public:
        inline RenderTargetsResetMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~RenderTargetsResetMsgArgs() {}
        inline StringRepr to_string() const override { return "RenderTargetsResetMsgArgs"; }
    };

    //
    // RenderDeviceResetMsgArgs
    //

    class RenderDeviceResetMsgArgs final : public AppMsgArgs {
    public:
        inline RenderDeviceResetMsgArgs(Tick time_stamp) : AppMsgArgs(time_stamp) {}
        inline ~RenderDeviceResetMsgArgs() {}
        inline StringRepr to_string() const override { return "RenderDeviceResetMsgArgs"; }
    };
}