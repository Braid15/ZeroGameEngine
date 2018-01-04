#include "Color.h"

namespace ZeroEngine {

    const Uint32 Color::_color_val_max = 255;
    const Uint32 Color::_color_val_min = 0;

    Color::Color(const Uint32& hex_color) {
        LOG_TODO("Color", "THIS ASSUMES LITTLE-ENDIAN");
        convert_from_hex(hex_color);
    }

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

    Color::Color(const Uint32& r, const Uint32& g, const Uint32& b, const Uint32& a) {
        set_red(r);
        set_green(g);
        set_blue(b);
        set_alpha(a);
    }

    bool Color::operator==(const Color& rhs) {
        return _red == rhs.get_red() 
            && _green == rhs.get_green()
            && _blue == rhs.get_blue()
            && _alpha == rhs.get_alpha();
    }

    bool Color::operator!=(const Color& rhs) {
        return _red != rhs.get_red()
            || _green != rhs.get_green()
            || _blue != rhs.get_blue()
            || _alpha != rhs.get_alpha();
    }

    Color& Color::operator=(const Color& rhs) {
        _red = rhs.get_red();
        _green = rhs.get_green();
        _blue = rhs.get_blue();
        _alpha = rhs.get_alpha();
        return *this;
    }

    Color& Color::operator=(const Color* rhs) {
        _red = rhs->get_red();
        _green = rhs->get_green();
        _blue = rhs->get_blue();
        _alpha = rhs->get_alpha();
        return *this;
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