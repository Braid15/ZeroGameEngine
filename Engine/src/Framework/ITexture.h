#pragma once

#include "../ZeroEngineStd.h"
#include "../Math/Vector2.h"
#include "../Math/Math.h"

namespace ZeroEngine {

    class ITexture : virtual public IZeroObject {
    public:
        virtual bool load() = 0;
        virtual void on_render() = 0;

        virtual const Vector2& get_dimensions() const = 0;
        virtual void set_dimensions(const float_t w, const float_t h) = 0;
        virtual void set_dimensions(const Vector2& dims) = 0;
        virtual void set_dimensions(const Vector2* dims) = 0;

        virtual float_t get_height() const = 0;
        virtual void set_height(const float_t height) = 0;

        virtual float_t get_width() const = 0;
        virtual void set_width(const float_t width) = 0;

        virtual const Vector2& get_position() const = 0;
        virtual void set_position(const Vector2& pos) = 0;
        virtual void set_position(const Vector2* pos) = 0;
        virtual void set_position(const float_t x, const float_t y) = 0;

        virtual float_t get_x() const = 0;
        virtual void set_x(const float_t x) = 0;

        virtual float_t get_y() const = 0;
        virtual void set_y(const float_t y) = 0;

        virtual StringRepr to_string() const = 0;
        virtual ~ITexture() {}
    };

    class BaseTexture : public ITexture {
    private:
        Vector2 _position;
        Vector2 _dimensions;
    public:
        virtual ~BaseTexture() {}
        virtual bool load() = 0;
        virtual void on_render() = 0;
        virtual StringRepr to_string() const = 0;

        virtual inline const Vector2& get_dimensions() const override { return _dimensions; }

        virtual inline void set_dimensions(const float_t w, const float_t h) override { 
            _dimensions.set(Math::clamp_min(w, 0.0f), Math::clamp_min(h, 0.0f)); 
        }

        virtual inline void set_dimensions(const Vector2& dims) override { 
            _dimensions.set_x(Math::clamp_min(dims.get_x(), 0.0f));
            _dimensions.set_y(Math::clamp_min(dims.get_y(), 0.0f));
        }

        virtual inline void set_dimensions(const Vector2* dims) override { 
            _dimensions.set_x(Math::clamp_min(dims->get_x(), 0.0f));
            _dimensions.set_y(Math::clamp_min(dims->get_y(), 0.0f));
        }

        virtual inline float_t get_height() const override { return _dimensions.get_y(); }
        virtual inline void set_height(const float_t height) override { _dimensions.set_y(Math::clamp_min(height, 0.0f)); }

        virtual inline float_t get_width() const override { return _dimensions.get_x(); }
        virtual inline void set_width(const float_t width) override { _dimensions.set_x(Math::clamp_min(width, 0.0f)); }

        virtual inline const Vector2& get_position() const override { return _position; }
        virtual inline void set_position(const Vector2& pos) override { _position.set(pos); }
        virtual inline void set_position(const Vector2* pos) override { _position.set(pos); }
        virtual inline void set_position(const float_t x, const float_t y) override { _position.set(x, y); }

        virtual inline float_t get_x() const override { return _position.get_x(); }
        virtual inline void set_x(const float_t x) override { _position.set_x(x); }

        virtual inline float_t get_y() const override { return _position.get_y(); }
        virtual inline void set_y(const float_t y) override { _position.set_y(y); }
    };
}