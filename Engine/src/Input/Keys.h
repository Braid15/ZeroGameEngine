#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    // @TODO: Unfinished

    enum class KeyCode : unsigned char;

    enum class KeyState : int8_t {
        null = -1,
        released = 0,
        pressed = 1
    };

    inline std::ostream& operator<<(std::ostream& os, KeyState keystate) {
        if (keystate == KeyState::released) {
            os << "KeyState::released";
        } else if (keystate == KeyState::pressed) {
            os << "KeyState::pressed";
        } else if (keystate == KeyState::null) {
            os << "KeyState::null";
        } else {
            os.setstate(std::ios_base::failbit);
        }
        return os;
    }

    enum class KeyMod : unsigned char {
        null = 0x00,
        begin = 0x01,
        left_shift,
        right_shift,
        left_alt,
        right_alt,
        left_control,
        right_control,
        caps_lock,
        end
    };

    inline std::ostream& operator<<(std::ostream& os, KeyMod mod) {
        if (mod == KeyMod::null) {
            os << "KeyMod::null";
        } else if (mod == KeyMod::begin) {
            os << "KeyMod::begin";
        } else if (mod == KeyMod::left_shift) {
            os << "KeyMod::left_shift";
        } else if (mod == KeyMod::right_shift) {
            os << "KeyMod::right_shift";
        } else if (mod == KeyMod::left_alt) {
            os << "KeyMod::left_alt";
        } else if (mod == KeyMod::right_alt) {
            os << "KeyMod::right_alt";
        } else if (mod == KeyMod::left_control) {
            os << "KeyMod::left_control";
        } else if (mod == KeyMod::right_control) {
            os << "KeyMod::right_control";
        } else if (mod == KeyMod::caps_lock) {
            os << "KeyMod::caps_lock";
        } else if (mod == KeyMod::end) {
            os << "KeyMod::end";
        } else {
            os.setstate(std::ios_base::failbit);
        }
        return os;
    }

    typedef std::array<KeyState, static_cast<int>(KeyMod::end)> KeyModStateArray;

    class Key : public IZeroObject {
    private:
        KeyCode _keycode;
        // @@TODO: There should only be one KeyModStateArray and each Key object
        // will have a reference to it
        KeyModStateArray _keymod_states;
        KeyState _state;
    public:
        inline Key() {}
        Key(KeyCode keycode, 
            KeyState state, 
            KeyModStateArray mods);
        inline ~Key() {}
        bool is_keymod_pressed(const KeyMod& mod) const;
        bool is_shift_pressed() const;
        bool is_alt_pressed() const;
        bool is_control_pressed() const;
        bool is_caps_lock_on() const;
        inline bool is_pressed() const { return _state == KeyState::pressed; }
        inline KeyState get_key_state() const { return _state; }
        char get_key_char() const;
        // @TODO: Trying to convert char to StringRepr prints out nonsense
        inline StringRepr to_string() const override { return "Key: FIX ME!"; }
    };

    enum class KeyCode : unsigned char {
        null = 0x00,
        enter = 0x0D,
        space = 0x20,
        exclamation = 0x21,
        double_quote = 0x22,
        hash = 0x23,
        dollar = 0x24,
        percent = 0x25,
        ampersand = 0x26,
        single_quote = 0x27,
        left_paren = 0x28,
        right_paren = 0x29,
        asterisk = 0x2A,
        plus = 0x2B,
        comma = 0x2C,
        minus = 0x2D,
        period = 0x2E,
        forward_slash = 0x2F,
        zero = 0x30,
        one = 0x31,
        two = 0x32,
        three = 0x33,
        four = 0x34,
        five = 0x35,
        six = 0x36,
        seven = 0x37,
        eight = 0x38,
        nine = 0x39,
        colon = 0x3A,
        semicolon = 0x3B,
        less_than = 0x3C,
        equal = 0x3D,
        greater_than = 0x3E,
        question_mark = 0x3F,
        at = 0x40,

        /*
        @ Capitals vs lowercase alphabetic chars only matter when getting the char
        A = 0x41,
        B = 0x42,
        C = 0x43,
        D = 0x44,
        E = 0x45,
        F = 0x46,
        G = 0x47,
        H = 0x48,
        I = 0x49,
        J = 0x4A,
        K = 0x4B,
        L = 0x4C,
        M = 0x4D,
        N = 0x4E,
        O = 0x4F,
        P = 0x50,
        Q = 0x51,
        R = 0x52,
        S = 0x53,
        T = 0x54,
        U = 0x55,
        V = 0x56,
        W = 0x57,
        X = 0x58,
        Y = 0x59,
        Z = 0x5A,
        */

        left_bracket = 0x5B,
        back_slash = 0x5C,
        right_bracket = 0x5D,
        caret = 0x5E,

        a = 0x61,
        b = 0x62,
        c = 0x63,
        d = 0x64,
        e = 0x65,
        f = 0x66,
        g = 0x67,
        h = 0x68,
        i = 0x69,
        j = 0x6A,
        k = 0x6B,
        l = 0x6C,
        m = 0x6D,
        n = 0x6E,
        o = 0x6F,
        p = 0x70,
        q = 0x71,
        r = 0x72,
        s = 0x73,
        t = 0x74,
        u = 0x75,
        v = 0x76,
        w = 0x77,
        x = 0x78,
        y = 0x79,
        z = 0x7A,

        left_brace = 0x7B,
        pipe = 0x7C,
        right_brace = 0x7D,
        tilda = 0x7E,
        escape = 0x7F,
        up = 0x80,
        right = 0x81,
        down = 0x82,
        left = 0x83,
        backspace = 0x84,

        // These keys also have corresponding KeyMod values
        left_shift = 0x85,
        right_shift = 0x86,
        left_alt = 0x87,
        right_alt = 0x88,
        left_control = 0x89,
        right_control = 0x8A,
        caps_lock = 0x8B,

        tab = 0x8C,
        del = 0x8D,
        underscore = 0x8E,
        page_down = 0x8F,
        page_up = 0x90,
    };
}