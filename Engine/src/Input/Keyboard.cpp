#include "Keyboard.h"

namespace ZeroEngine {

    std::array<KeyState, static_cast<int>(Key::end)> Keyboard::_keyboard_state = { KeyState::released };

    bool Keyboard::is_pressed(const Key& keycode) {
        return _keyboard_state[static_cast<int>(keycode)] == KeyState::pressed;
    }

    void Keyboard::set(const KeyboardMsg* const msg) {
        _keyboard_state[static_cast<int>(msg->get_key())] = msg->get_key_state();
    }
}