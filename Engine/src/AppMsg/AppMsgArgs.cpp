#include "AppMsgArgs.h"

namespace ZeroEngine {

    //
    // MouseMotionMsgArgs
    //
    
    MouseMotionMsgArgs::MouseMotionMsgArgs(Tick time_stamp, uint32 window, uint32 mouse, MouseButtonStateArray buttons,
                                           int32 x_pos, int32 y_pos, int32 x_rel, int32 y_rel) : AppMsgArgs(time_stamp) {
        _window = window;
        _mouse_id = mouse;
        for (int32 i = static_cast<int32>(MouseButton::begin); i < static_cast<int32>(MouseButton::end); ++i) {
            _button_states[i] = buttons[i];
        }
        _x_y_coordinates.set(x_pos, y_pos);
        _x_y_relative.set(x_rel, y_rel);
    }

    bool MouseMotionMsgArgs::is_pressed(MouseButton button) const {
        return _button_states[static_cast<int32>(button)] == ButtonState::pressed;
    }

    // 
    // MouseButtonMsgArgs
    //

    MouseButtonMsgArgs::MouseButtonMsgArgs(Tick time_stamp, uint32 window, uint32 mouse_id,
                        ButtonState state, uint8 num_clicks, MouseButton button, int32 x_pos, int32 y_pos) 
                        : AppMsgArgs(time_stamp) {
        _window = window;
        _mouse_id = mouse_id;
        _state = state;
        _clicks = num_clicks;
        _button = button;
        _x_y_coordinates = Point<int32>(x_pos, y_pos);
    }

    //
    // MouseWheelMsgArgs
    //

    MouseWheelMsgArgs::MouseWheelMsgArgs(Tick time_stamp, uint32 window, uint32 mouse,
                                         int32 x, int32 y, MouseWheelDirection direction)
                                         : AppMsgArgs(time_stamp) {
        _window = window;
        _mouse_id = mouse;
        _x_y_coordinates.set(x, y);
        _direction = direction;
    }


    //
    // KeyboardMsgArgs
    //

    KeyboardMsgArgs::KeyboardMsgArgs(Tick time_stamp, uint32 window, Key& key, bool repeat, 
                                     KeyState state, KeyModStateArray mod_states)
                                     : AppMsgArgs(time_stamp) {
        _key_state = state;
        _window = window;
        _key = key;
        _is_repeat = repeat;
        _keymod_states = mod_states;
    }
}