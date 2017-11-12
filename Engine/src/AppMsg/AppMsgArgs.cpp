#include "AppMsgArgs.h"

namespace ZeroEngine {


    //
    // MouseMotionMsgArgs
    //

    MouseMotionMsgArgs::MouseMotionMsgArgs(Time time_stamp, uint32_t window, uint32_t mouse, ButtonState buttons[static_cast<int>(MouseButton::end)],
                                           int32_t x_pos, int32_t y_pos, int32_t x_rel, int32_t y_rel) : AppMsgArgs(time_stamp) {
        _window = window;
        _mouse_id = mouse;
        for (int i = static_cast<int>(MouseButton::begin); i < static_cast<int>(MouseButton::end); ++i) {
            _buttons[i] = buttons[i];
        }
        _x_y_coordinates.set(x_pos, y_pos);
        _x_y_relative.set(x_rel, y_rel);
    }

    bool MouseMotionMsgArgs::is_pressed(MouseButton button) const {
        return _buttons[static_cast<int>(button)] == ButtonState::pressed;
    }

    // 
    // MouseButtonMsgArgs
    //

    MouseButtonMsgArgs::MouseButtonMsgArgs(Time time_stamp, uint32_t window, uint32_t mouse_id,
                        ButtonState state, uint8_t num_clicks, MouseButton button, int32_t x_pos, int32_t y_pos) 
                        : AppMsgArgs(time_stamp) {
        _window = window;
        _mouse_id = mouse_id;
        _state = state;
        _clicks = num_clicks;
        _button = button;
        _x_y_coordinates = Point<int32_t>(x_pos, y_pos);
    }

    //
    // KeyboardMsgArgs
    //

    KeyboardMsgArgs::KeyboardMsgArgs(Time time_stamp, uint32_t window, Key& key, bool repeat, KeyState state)
                                     : AppMsgArgs(time_stamp) {
        _window = window;
        _key = key;
        _is_repeat = repeat;
        _state = state;
    }

                            
}