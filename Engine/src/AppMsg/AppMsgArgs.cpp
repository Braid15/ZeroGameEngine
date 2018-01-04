#include "AppMsgArgs.h"

namespace ZeroEngine {

    //
    // MouseMotionMsgArgs
    //
    
    MouseMotionMsgArgs::MouseMotionMsgArgs(Tick time_stamp, Uint32 window, Uint32 mouse, MouseButtonStateArray buttons,
                                           Int32 x_pos, Int32 y_pos, Int32 x_rel, Int32 y_rel) : AppMsgArgs(time_stamp) {
        _window = window;
        _mouse_id = mouse;
        for (Int32 i = static_cast<Int32>(MouseButton::begin); i < static_cast<Int32>(MouseButton::end); ++i) {
            _button_states[i] = buttons[i];
        }
        _x_y_coordinates.set(x_pos, y_pos);
        _x_y_relative.set(x_rel, y_rel);
    }

    bool MouseMotionMsgArgs::is_pressed(MouseButton button) const {
        return _button_states[static_cast<Int32>(button)] == ButtonState::pressed;
    }

    // 
    // MouseButtonMsgArgs
    //

    MouseButtonMsgArgs::MouseButtonMsgArgs(Tick time_stamp, Uint32 window, Uint32 mouse_id,
                        ButtonState state, Uint8 num_clicks, MouseButton button, Int32 x_pos, Int32 y_pos) 
                        : AppMsgArgs(time_stamp) {
        _window = window;
        _mouse_id = mouse_id;
        _state = state;
        _clicks = num_clicks;
        _button = button;
        _x_y_coordinates = Point<Int32>(x_pos, y_pos);
    }

    //
    // MouseWheelMsgArgs
    //

    MouseWheelMsgArgs::MouseWheelMsgArgs(Tick time_stamp, Uint32 window, Uint32 mouse,
                                         Int32 x, Int32 y, MouseWheelDirection direction)
                                         : AppMsgArgs(time_stamp) {
        _window = window;
        _mouse_id = mouse;
        _x_y_coordinates.set(x, y);
        _direction = direction;
    }


    //
    // KeyboardMsgArgs
    //

    KeyboardMsgArgs::KeyboardMsgArgs(Tick time_stamp, Uint32 window, Key& key, bool repeat, 
                                     KeyState state, KeyModStateArray mod_states)
                                     : AppMsgArgs(time_stamp) {
        _key_state = state;
        _window = window;
        _key = key;
        _is_repeat = repeat;
        _keymod_states = mod_states;
    }
}