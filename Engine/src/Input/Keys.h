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
        inline KeyState key_state() const { return _state; }
        inline bool equals(const KeyCode& keycode) const { return _keycode == keycode; }
        inline const KeyCode keycode() const { return _keycode; }
        char get_key_char() const;
        // @TODO: Trying to convert char to StringRepr prints out nonsense
        inline StringRepr to_string() const override { return "Key: FIX ME!"; }
    };

    // @TODO: I Might factor these values into Key class just for convenience.
    // Ex. key == Key::w rather than key.equals(KeyCode::w)
    enum class KeyCode : unsigned char {
        null = 0x00,
        begin = 0x01,
        enter = 0x01,
        space,
        exclamation,
        double_quote,
        hash,
        dollar,
        percent,
        ampersand,
        single_quote,
        left_paren,
        right_paren,
        asterisk,
        plus,
        comma,
        minus,
        period,
        forward_slash,
        zero,
        one,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        colon,
        semicolon,
        less_than,
        equal,
        greater_than,
        question_mark,
        at,

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

        left_bracket,
        back_slash,
        right_bracket,
        caret,
        a,
        b,
        c,
        d,
        e,
        f,
        g,
        h,
        i,
        j,
        k,
        l,
        m,
        n,
        o,
        p,
        q,
        r,
        s,
        t,
        u,
        v,
        w,
        x,
        y,
        z,
        left_brace,
        pipe,
        right_brace,
        tilda,
        escape,
        up,
        right,
        down,
        left,
        backspace,

        // These keys also have corresponding KeyMod values
        left_shift,
        right_shift,
        left_alt,
        right_alt,
        left_control,
        right_control,
        caps_lock,

        tab,
        del,
        underscore,
        page_down,
        page_up,
        end
    };
}