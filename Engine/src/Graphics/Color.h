#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    typedef Uint32 HexColorCode;

    class Color : public IZeroObject {
    private:
        static const Uint32 _color_val_max;
        static const Uint32 _color_val_min;

        Uint32 _red;
        Uint32 _green;
        Uint32 _blue;
        Uint32 _alpha;
    public:
        inline Color() : _red(0), _green(0), _blue(0), _alpha(0) {}
        Color(const Uint32& hex_color);
        Color(const Color* other);
        Color(const Color& other);
        Color(const Uint32& r, const Uint32& g, const Uint32& b, const Uint32& a);
        virtual ~Color() {}
        inline Uint32 get_red() const { return _red; }
        inline Uint32 get_green() const { return _green; }
        inline Uint32 get_blue() const { return _blue; }
        inline Uint32 get_alpha() const { return _alpha; }
        inline void set_red(const Uint32& value);
        inline void set_green(const Uint32& value);
        inline void set_blue(const Uint32& value);
        inline void set_alpha(const Uint32& value);
        inline void set(const Uint32& red, const Uint32& green,
                        const Uint32& blue, const Uint32& alpha);
        inline void set(const Uint32& hex_color);
        inline StringRepr to_string() const { return "Color"; }

        bool operator==(const Color& rhs);
        bool operator!=(const Color& rhs);
        Color& operator=(const Color& rhs);
        Color& operator=(const Color* rhs);

        // @TODO: Other operators

    private:
        inline void convert_from_hex(const Uint32& hex_color);
        inline void set_color_value(Uint32* color, const Uint32& value);
    };

   inline void Color::set_color_value(Uint32* color, const Uint32& value) {
        if (_color_val_min <= value && value <= _color_val_max) {
            *color = value;
        } else if (value < _color_val_min) {
            *color = _color_val_min;
        } else if (value > _color_val_max) {
            *color = _color_val_max;
        }
    }

   inline void Color::set(const Uint32& r, const Uint32& g, const Uint32& b, const Uint32& a) {
       set_red(r);
       set_green(g);
       set_blue(b);
       set_alpha(a);
   }

   inline void Color::set(const Uint32& hex_color) {
       LOG_TODO("Color", "THIS ASSUMES LITTLE-ENDIAN!!!");
       convert_from_hex(hex_color);
   }

    inline void Color::set_red(const Uint32& value) {
        set_color_value(&_red, value);
    }

    inline void Color::set_green(const Uint32& value) {
        set_color_value(&_green, value);
    }

    inline void Color::set_blue(const Uint32& value) {
        set_color_value(&_blue, value);
    }

    inline void Color::set_alpha(const Uint32& value) {
        set_color_value(&_alpha, value);
    }

    inline void Color::convert_from_hex(const Uint32& hex_color) {
        Uint8* bits = (Uint8*)&hex_color;
        set_alpha(*bits);
        set_blue(*(bits + 0x1));
        set_green(*(bits + 0x2));
        set_red(*(bits + 0x3));
    }

    // ------
    // Colors
    // ------

    // @TODO: Move to sepearte file

    class Colors {
    public:
        static Color blue();
        static Color red();
        static Color green();
        static Color white();
        static Color black();

    private:
        inline Colors() {}
        inline Colors(const Colors&) {}
    };
}