#pragma once

#include "../ZeroEngineStd.h"
#include "../AppMsg/AppMsg.h"
#include "Keys.h"

namespace ZeroEngine {

    // This will be a static class which contains internal data about the present state of the keyboard.
    // The idea is so that client code doesn't need to get this data by watching for KeyboardMsg, but
    // can get this data at anypoint by calling this class
    class Keyboard {
    private:
        static std::array<KeyState, static_cast<int>(Keys::end)> _keyboard_state;
        // Keymod states
    public:
        inline ~Keyboard() {}
        static bool is_pressed(const Keys& keycode);
        // @TEMP: I want a more private way to set the state
        static void set(const KeyboardMsg* const);
    private:
        inline Keyboard() {}
        inline Keyboard(const Keyboard&) {}
    };
}