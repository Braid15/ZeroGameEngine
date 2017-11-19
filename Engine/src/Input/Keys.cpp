#include "Keys.h"

namespace ZeroEngine {

    Key::Key(KeyCode keycode, KeyState state, KeyModStateArray keymods) {
        _keycode = keycode;
        _state = state;
        _keymod_states = keymods;
    }

    // @FIX: These arent working when multiple mods are pressed
    bool Key::is_keymod_pressed(const KeyMod& keymod) const {
        return _keymod_states[static_cast<int>(keymod)] == KeyState::pressed;
    }

    bool Key::is_alt_pressed() const {
        return _keymod_states[static_cast<int>(KeyMod::left_alt)] == KeyState::pressed
           || _keymod_states[static_cast<int>(KeyMod::right_alt)] == KeyState::pressed;
    }

    bool Key::is_shift_pressed() const {
        return _keymod_states[static_cast<int>(KeyMod::left_shift)] == KeyState::pressed
            || _keymod_states[static_cast<int>(KeyMod::right_shift)] == KeyState::pressed;
    }

    bool Key::is_control_pressed() const {
        return _keymod_states[static_cast<int>(KeyMod::left_control)] == KeyState::pressed
            || _keymod_states[static_cast<int>(KeyMod::right_control)] == KeyState::pressed;
    }

    bool Key::is_caps_lock_on() const {
        return _keymod_states[static_cast<int>(KeyMod::caps_lock)] == KeyState::pressed;
    }
}