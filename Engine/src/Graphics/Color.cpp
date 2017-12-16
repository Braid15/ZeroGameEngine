#include "Color.h"

namespace ZeroEngine {

    static const uint32_t COLOR_VAL_MAX = 255;
    static const uint32_t COLOR_VAL_MIN = 0;

    Color::Color(const Color* other) {
        _red = other->get_red();
        _green = other->get_green();
        _blue = other->get_blue();
        _alpha = other->get_alpha();
    }

    Color::Color(const Color& other) {
        _red = other.get_red();
        _green = other.get_green();
        _blue = other.get_blue();
        _alpha = other.get_alpha();
    }

    Color::Color(const uint32_t r, const uint32_t g, const uint32_t b, const uint32_t a) {
        set_red(r);
        set_green(g);
        set_blue(b);
        set_alpha(a);
    }

    inline void Color::set_color_value(uint32_t* color, const uint32_t value) {
        if (COLOR_VAL_MIN <= value && value <= COLOR_VAL_MAX) {
            *color = value;
        } else if (value < COLOR_VAL_MIN) {
            *color = COLOR_VAL_MIN;
        } else if (value > COLOR_VAL_MAX) {
            *color = COLOR_VAL_MAX;
        }
    }

    inline void Color::set_red(const uint32_t value) {
        set_color_value(&_red, value);
    }

    inline void Color::set_green(const uint32_t value) {
        set_color_value(&_green, value);
    }

    inline void Color::set_blue(const uint32_t value) {
        set_color_value(&_blue, value);
    }

    inline void Color::set_alpha(const uint32_t value) {
        set_color_value(&_alpha, value);
    }

    //
    // Colors
    //

    Color Colors::blue() {
        return Color(0, 0, 255, 255);
    }

    Color Colors::red() {
        return Color(255, 0, 0, 255);
    }

    Color Colors::green() {
        return Color(0, 255, 0, 255);
    }

    Color Colors::white() {
        return Color(255, 255, 255, 255);
    }

    Color Colors::black() {
        return Color(0, 0, 0, 255);
    }
}