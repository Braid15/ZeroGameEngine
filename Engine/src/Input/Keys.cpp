#include "Keys.h"
#include "Keyboard.h"

namespace ZeroEngine {

    bool Key_is(const Key& key1, const Key& key2) {
        return key1 == key2;
    }

    bool Key_is_numeric(const Key& key) {
        uint32_t key_val = static_cast<uint32_t>(key);
        return 0x2F < key_val && key_val < 0x3A;
    }

    const uint32_t INVALID_NUMERIC_KEY = 0xffffffff;
    uint32_t Key_get_numeric_value(const Key& key) {
        if (Key_is_numeric(key)) {
            return static_cast<uint32_t>(key) - 0x30;
        }
        return INVALID_NUMERIC_KEY;
    }

    // This depends on the order in which the keys are declared in the enum
    bool Key_is_alpha(const Key& key) {
        uint32_t hex_val = static_cast<uint32_t>(key);
        // The enum only contains lower case characters
        return 0x60 < hex_val && hex_val < 0x7B;
    }

    bool Key_is_alpha_numeric(const Key& key) {
        return Key_is_alpha(key) || Key_is_numeric(key);
    }

    char Key_get_char(const Key& key) {
        char ret_char = 0x00;
        if (Key_is_alpha(key)) {
            ret_char = static_cast<char>(key);
            if (Keyboard::is_pressed(Key::left_shift) || Keyboard::is_pressed(Key::right_shift)) {
                ret_char = static_cast<char>(key) - 0x20;
            }
        }
        return ret_char;
    }
}