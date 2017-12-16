#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class Color : public IZeroObject {
    private:
        uint32_t _red;
        uint32_t _green;
        uint32_t _blue;
        uint32_t _alpha;
    public:
        inline Color() : _red(0), _green(0), _blue(0), _alpha(0) {}
        Color(const Color* other);
        Color(const Color& other);
        Color(const uint32_t r, const uint32_t g, const uint32_t b, const uint32_t a);
        virtual ~Color() {}
        inline uint32_t get_red() const { return _red; }
        inline uint32_t get_green() const { return _green; }
        inline uint32_t get_blue() const { return _blue; }
        inline uint32_t get_alpha() const { return _alpha; }
        void set_red(const uint32_t value);
        inline void set_green(const uint32_t value);
        inline void set_blue(const uint32_t value);
        inline void set_alpha(const uint32_t value);
        inline StringRepr to_string() const { return "Color"; }
    private:
        inline void set_color_value(uint32_t* color, const uint32_t value);
    };

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