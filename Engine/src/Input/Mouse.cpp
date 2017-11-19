#include "Mouse.h"

namespace ZeroEngine {

    std::array<ButtonState, static_cast<int>(MouseButton::end)> Mouse::_button_states = { ButtonState::released };

    Point<int32_t> Mouse::_pointer_position(0, 0);

    bool Mouse::is_pressed(const MouseButton& button) {
        return _button_states[static_cast<int>(button)] == ButtonState::pressed;
    }

    const Point<int32_t>& Mouse::position() {
        return _pointer_position;
    }

    void Mouse::set(const MouseMotionMsg* const msg) {
        _pointer_position.set(msg->get_x_pos(), msg->get_y_pos());
    }


}