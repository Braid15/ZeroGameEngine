#include "Mouse.h"

namespace ZeroEngine {

    std::array<ButtonState, static_cast<Int32>(MouseButton::end)> Mouse::_button_states = { ButtonState::released };

    Point<Int32> Mouse::_pointer_position(0, 0);

    MouseWheelDirection Mouse::_wheel_direction = MouseWheelDirection::null;

    bool Mouse::is_pressed(const MouseButton& button) {
        return _button_states[static_cast<Int32>(button)] == ButtonState::pressed;
    }

    const Point<Int32>& Mouse::position() {
        return _pointer_position;
    }

    /*
    const MouseWheelDirection& Mouse::wheel_direction() {
        return _wheel_direction;
    }
    */

    void Mouse::set(const MouseMotionMsg* const msg) {
        _pointer_position.set(msg->get_x_pos(), msg->get_y_pos());
    }

    void Mouse::set(const MouseButtonMsg* const msg) {
        _button_states[static_cast<Int32>(msg->get_button())] = msg->get_state();
    }

    void Mouse::set(const MouseWheelMsg* const msg) {
        _wheel_direction = msg->get_direction();
    }
}