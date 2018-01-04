#include "Keyboard.h"

namespace ZeroEngine {

    std::array<KeyState, static_cast<Int32>(Key::end_enum)> Keyboard::_keyboard_state = { KeyState::released };

    bool Keyboard::is_pressed(const Key& keycode) {
        return _keyboard_state[static_cast<Int32>(keycode)] == KeyState::pressed;
    }

    void Keyboard::set(const KeyboardMsg* const msg) {
        _keyboard_state[static_cast<Int32>(msg->get_key())] = msg->get_key_state();
    }
}