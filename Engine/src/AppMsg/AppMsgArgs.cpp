#include "AppMsgArgs.h"

namespace ZeroEngine {


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