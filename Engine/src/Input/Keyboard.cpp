#include "Keyboard.h"

namespace ZeroEngine {

    std::array<KeyState, static_cast<int32>(Key::end_enum)> Keyboard::_keyboard_state = { KeyState::released };

    bool Keyboard::is_pressed(const Key& keycode) {
        return _keyboard_state[static_cast<int32>(keycode)] == KeyState::pressed;
    }

    void Keyboard::set(const KeyboardMsg* const msg) {
        _keyboard_state[static_cast<int32>(msg->get_key())] = msg->get_key_state();
    }
}