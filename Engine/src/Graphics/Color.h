#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    typedef uint32 HexColorCode;

    class Color : public IZeroObject {
    private:
        static const uint32 _color_val_max;
        static const uint32 _color_val_min;

        uint32 _red;
        uint32 _green;
        uint32 _blue;
        uint32 _alpha;
    public:
        inline Color() : _red(0), _green(0), _blue(0), _alpha(0) {}
        Color(const uint32& hex_color);
        Color(const Color* other);
        Color(const Color& other);
        Color(const uint32& r, const uint32& g, const uint32& b, const uint32& a);
        virtual ~Color() {}
        inline uint32 get_red() const { return _red; }
        inline uint32 get_green() const { return _green; }
        inline uint32 get_blue() const { return _blue; }
        inline uint32 get_alpha() const { return _alpha; }
        inline void set_red(const uint32& value);
        inline void set_green(const uint32& value);
        inline void set_blue(const uint32& value);
        inline void set_alpha(const uint32& value);
        inline void set(const uint32& red, const uint32& green,
                        const uint32& blue, const uint32& alpha);
        inline void set(const uint32& hex_color);
        inline StringRepr to_string() const { return "Color"; }

        bool operator==(const Color& rhs);
        bool operator!=(const Color& rhs);
        Color& operator=(const Color& rhs);
        Color& operator=(const Color* rhs);

        // @TODO: Other operators

    private:
        inline void convert_from_hex(const uint32& hex_color);
        inline void set_color_value(uint32* color, const uint32& value);
    };

   inline void Color::set_color_value(uint32* color, const uint32& value) {
        if (_color_val_min <= value && value <= _color_val_max) {
            *color = value;
        } else if (value < _color_val_min) {
            *color = _color_val_min;
        } else if (value > _color_val_max) {
            *color = _color_val_max;
        }
    }

   inline void Color::set(const uint32& r, const uint32& g, const uint32& b, const uint32& a) {
       set_red(r);
       set_green(g);
       set_blue(b);
       set_alpha(a);
   }

   inline void Color::set(const uint32& hex_color) {
       LOG_TODO("Color", "THIS ASSUMES LITTLE-ENDIAN!!!");
       convert_from_hex(hex_color);
   }

    inline void Color::set_red(const uint32& value) {
        set_color_value(&_red, value);
    }

    inline void Color::set_green(const uint32& value) {
        set_color_value(&_green, value);
    }

    inline void Color::set_blue(const uint32& value) {
        set_color_value(&_blue, value);
    }

    inline void Color::set_alpha(const uint32& value) {
        set_color_value(&_alpha, value);
    }

    inline void Color::convert_from_hex(const uint32& hex_color) {
        uint8* bits = (uint8*)&hex_color;
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