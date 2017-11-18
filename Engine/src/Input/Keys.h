#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    // @TODO: Unfinished

    enum class KeyValue : unsigned char;

    class Key : public IZeroObject {
    private:
        KeyValue _value;
    public:
        inline Key() {}
        inline Key(KeyValue value) : _value(value) {}
        inline ~Key() {}
        inline char get_key_char() const { return static_cast<char>(_value); }
        // @TODO: Trying to convert char to StringRepr prints out nonsense
        inline StringRepr to_string() const override { return "Key: FIX ME!"; }
    };

    // @TODO: Maybe KeyState is not needed since there are seperate classes for KeyDown and KeyUp?
    enum class KeyState : unsigned char {
        released = 0x00,
        pressed = 0xFF
    };

    enum class KeyValue : unsigned char {
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
    };
}