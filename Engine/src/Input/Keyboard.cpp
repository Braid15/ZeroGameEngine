#include "Keyboard.h"

namespace ZeroEngine {

    std::array<KeyState, static_cast<int>(KeyCode::end)> Keyboard::_keyboard_state = { KeyState::released };

    bool Keyboard::is_pressed(const KeyCode& keycode) {
        return _keyboard_state[static_cast<int>(keycode)] == KeyState::pressed;
    }

    void Keyboard::set(const KeyboardMsg* const msg) {
        _keyboard_state[static_cast<int>(msg->key().keycode())] = msg->key().key_state();
    }
}