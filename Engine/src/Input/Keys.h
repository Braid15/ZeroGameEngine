#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    // @TODO: Unfinished

    enum class Key : unsigned char;

    enum class KeyState : int8 {
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

    typedef std::array<KeyState, static_cast<int32>(KeyMod::end)> KeyModStateArray;

    // @TODO: Make this completely equal to ascii values
    enum class Key : unsigned char {
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
        zero = 0x30,
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

        left_bracket = 0x5B,
        back_slash,
        right_bracket,
        caret,
        a = 0x61,
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
        end_enum
    };

    extern bool Key_is(const Key& key1, const Key& key2);
    extern bool Key_is_numeric(const Key& key);

    extern const uint32 INVALID_NUMERIC_KEY;
    extern uint32 Key_get_numeric_value(const Key& key);

    extern bool Key_is_alpha(const Key& key);
    extern bool Key_is_alpha_numeric(const Key& key);
    extern char Key_get_char(const Key& key);


    inline std::ostream& operator<<(std::ostream& os, Key key) {
        switch (key) {
            case Key::null:
            {
                os << "Key::null";
                break;
            }
            case Key::enter:
            {
                os << "Key::enter";
                break;
            }
            case Key::space:
            {
                os << "Key::space";
                break;
            }
            case Key::exclamation:
            {
                os << "Key::exclamation";
                break;
            }
            case Key::double_quote:
            {
                os << "Key::double_quote";
                break;
            }
            case Key::hash:
            {
                os << "Key::hash";
                break;
            }
            case Key::dollar:
            {
                os << "Key::dollar";
                break;
            }
            case Key::percent:
            {
                os << "Key::percent";
                break;
            }
            case Key::ampersand:
            {
                os << "Key::ampersand";
                break;
            }
            case Key::single_quote:
            {
                os << "Key::single_quote";
                break;
            }
            case Key::left_paren:
            {
                os << "Key::left_paren";
                break;
            }
            case Key::right_paren:
            {
                os << "Key::right_paren";
                break;
            }
            case Key::asterisk:
            {
                os << "Key::asterisk";
                break;
            }
            case Key::plus:
            {
                os << "Key::plus";
                break;
            }
            case Key::comma:
            {
                os << "Key::comma";
                break;
            }
            case Key::minus:
            {
                os << "Key::minus";
                break;
            }
            case Key::period:
            {
                os << "Key::period";
                break;
            }
            case Key::forward_slash:
            {
                os << "Key::forward_slash";
                break;
            }
            case Key::zero:
            {
                os << "Key::zero";
                break;
            }
            case Key::one:
            {
                os << "Key::one";
                break;
            }
            case Key::two:
            {
                os << "Key::two";
                break;
            }
            case Key::three:
            {
                os << "Key::three";
                break;
            }
            case Key::four:
            {
                os << "Key::four";
                break;
            }
            case Key::five:
            {
                os << "Key::five";
                break;
            }
            case Key::six:
            {
                os << "Key::six";
                break;
            }
            case Key::seven:
            {
                os << "Key::seven";
                break;
            }
            case Key::eight:
            {
                os << "Key::eight";
                break;
            }
            case Key::nine:
            {
                os << "Key::nine";
                break;
            }
            case Key::colon:
            {
                os << "Key::colon";
                break;
            }
            case Key::semicolon:
            {
                os << "Key::semicolon";
                break;
            }
            case Key::less_than:
            {
                os << "Key::less_than";
                break;
            }
            case Key::equal:
            {
                os << "Key::equal";
                break;
            }
            case Key::greater_than:
            {
                os << "Key::greater_than";
                break;
            }
            case Key::question_mark:
            {
                os << "Key::question_mark";
                break;
            }
            case Key::at:
            {
                os << "Key::at";
                break;
            }
            case Key::left_bracket:
            {
                os << "Key::left_bracket";
                break;
            }
            case Key::back_slash:
            {
                os << "Key::back_slash";
                break;
            }
            case Key::right_bracket:
            {
                os << "Key::right_bracket";
                break;
            }
            case Key::caret:
            {
                os << "Key::caret";
                break;
            }
            case Key::a:
            {
                os << "Key::a";
                break;
            }
            case Key::b:
            {
                os << "Key::b";
                break;
            }
            case Key::c:
            {
                os << "Key::c";
                break;
            }
            case Key::d:
            {
                os << "Key::d";
                break;
            }
            case Key::e:
            {
                os << "Key::e";
                break;
            }
            case Key::f:
            {
                os << "Key::f";
                break;
            }
            case Key::g:
            {
                os << "Key::g";
                break;
            }
            case Key::h:
            {
                os << "Key::h";
                break;
            }
            case Key::i:
            {
                os << "Key::i";
                break;
            }
            case Key::j:
            {
                os << "Key::j";
                break;
            }
            case Key::k:
            {
                os << "Key::k";
                break;
            }
            case Key::l:
            {
                os << "Key::l";
                break;
            }
            case Key::m:
            {
                os << "Key::m";
                break;
            }
            case Key::n:
            {
                os << "Key::n";
                break;
            }
            case Key::o:
            {
                os << "Key::o";
                break;
            }
            case Key::p:
            {
                os << "Key::p";
                break;
            }
            case Key::q:
            {
                os << "Key::q";
                break;
            }
            case Key::r:
            {
                os << "Key::r";
                break;
            }
            case Key::s:
            {
                os << "Key::s";
                break;
            }
            case Key::t:
            {
                os << "Key::t";
                break;
            }
            case Key::u:
            {
                os << "Key::u";
                break;
            }
            case Key::v:
            {
                os << "Key::v";
                break;
            }
            case Key::w:
            {
                os << "Key::w";
                break;
            }
            case Key::x:
            {
                os << "Key::x";
                break;
            }
            case Key::y:
            {
                os << "Key::y";
                break;
            }
            case Key::z:
            {
                os << "Key::z";
                break;
            }
            case Key::left_brace:
            {
                os << "Key::left_brace";
                break;
            }
            case Key::pipe:
            {
                os << "Key::pipe";
                break;
            }
            case Key::right_brace:
            {
                os << "Key::right_brace";
                break;
            }
            case Key::tilda:
            {
                os << "Key::tilda";
                break;
            }
            case Key::escape:
            {
                os << "Key::escape";
                break;
            }
            case Key::up:
            {
                os << "Key::up";
                break;
            }
            case Key::right:
            {
                os << "Key::right";
                break;
            }
            case Key::down:
            {
                os << "Key::down";
                break;
            }
            case Key::left:
            {
                os << "Key::left";
                break;
            }
            case Key::backspace:
            {
                os << "Key::backspace";
                break;
            }
            case Key::left_shift:
            {
                os << "Key::left_shift";
                break;
            }
            case Key::right_shift:
            {
                os << "Key::right_shift";
                break;
            }
            case Key::left_alt:
            {
                os << "Key::left_alt";
                break;
            }
            case Key::right_alt:
            {
                os << "Key::right_alt";
                break;
            }
            case Key::left_control:
            {
                os << "Key::left_control";
                break;
            }
            case Key::right_control:
            {
                os << "Key::right_control";
                break;
            }
            case Key::caps_lock:
            {
                os << "Key::caps_lock";
                break;
            }
            case Key::tab:
            {
                os << "Key::tab";
                break;
            }
            case Key::del:
            {
                os << "Key::del";
                break;
            }
            case Key::underscore:
            {
                os << "Key::underscore";
                break;
            }
            case Key::page_down:
            {
                os << "Key::page_down";
                break;
            }
            case Key::page_up:
            {
                os << "Key::page_up";
                break;
            }
            case Key::end_enum:
            {
                os << "Key::end_enum";
                break;
            }
            default:
            {
                os.setstate(std::ios_base::failbit);
            }
        }
        return os;
    }
}