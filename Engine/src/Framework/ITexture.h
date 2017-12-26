#pragma once

#include "../ZeroEngineStd.h"

namespace ZeroEngine {

    class ITexture : virtual public IZeroObject {
    public:
        virtual bool load() = 0;
        virtual void on_render() = 0;
        virtual uint32_t get_height() const = 0;
        virtual uint32_t get_width() const = 0;
        virtual int32_t get_x() const = 0;
        virtual int32_t get_y() const = 0;
        virtual void set_x(const int32_t x) = 0;
        virtual void set_y(const int32_t y) = 0;
        virtual void set_width(const uint32_t width) = 0;
        virtual void set_height(const uint32_t height) = 0;
        virtual StringRepr to_string() const = 0;
        virtual ~ITexture() {}
    };

    class BaseTexture : public ITexture {
    private:
        uint32_t _height;
        uint32_t _width;
        int32_t _x;
        int32_t _y;
    public:
        virtual bool load() = 0;
        virtual void on_render() = 0;
        virtual StringRepr to_string() const = 0;

        virtual inline uint32_t get_height() const override { return _height; }
        virtual inline uint32_t get_width() const override { return _width; }
        virtual inline int32_t get_x() const override { return _x; }
        virtual inline int32_t get_y() const override { return _y; }
        virtual inline void set_x(const int32_t x) override { _x = x; }
        virtual inline void set_y(const int32_t y) override { _y = y; }
        virtual inline void set_width(const uint32_t width) override { _width = width; }
        virtual inline void set_height(const uint32_t height) override { _height = height; }
        virtual ~BaseTexture() {}
    };
}