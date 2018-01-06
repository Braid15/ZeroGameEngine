#pragma once

#include "../ZeroEngineStd.h"
#include "../Math/MathTypes.h"
#include "../Math/Math.h"

namespace ZeroEngine {

    class ITexture : virtual public IZeroObject {
    public:
        virtual bool load() = 0;
        virtual void on_render() = 0;

        virtual const Vector2& get_dimensions() const = 0;
        virtual void set_dimensions(const Float32 w, const Float32 h) = 0;
        virtual void set_dimensions(const Vector2& dims) = 0;
        virtual void set_dimensions(const Vector2* dims) = 0;

        virtual Float32 get_height() const = 0;
        virtual void set_height(const Float32 height) = 0;

        virtual Float32 get_width() const = 0;
        virtual void set_width(const Float32 width) = 0;

        virtual const Vector2& get_position() const = 0;
        virtual void set_position(const Vector2& pos) = 0;
        virtual void set_position(const Vector2* pos) = 0;
        virtual void set_position(const Float32 x, const Float32 y) = 0;

        virtual Float32 get_x() const = 0;
        virtual void set_x(const Float32 x) = 0;

        virtual Float32 get_y() const = 0;
        virtual void set_y(const Float32 y) = 0;

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

        virtual inline void set_dimensions(const Float32 w, const Float32 h) override { 
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

        virtual inline Float32 get_height() const override { return _dimensions.get_y(); }
        virtual inline void set_height(const Float32 height) override { _dimensions.set_y(Math::clamp_min(height, 0.0f)); }

        virtual inline Float32 get_width() const override { return _dimensions.get_x(); }
        virtual inline void set_width(const Float32 width) override { _dimensions.set_x(Math::clamp_min(width, 0.0f)); }

        virtual inline const Vector2& get_position() const override { return _position; }
        virtual inline void set_position(const Vector2& pos) override { _position.set(pos); }
        virtual inline void set_position(const Vector2* pos) override { _position.set(*pos); }
        virtual inline void set_position(const Float32 x, const Float32 y) override { _position.set(x, y); }

        virtual inline Float32 get_x() const override { return _position.get_x(); }
        virtual inline void set_x(const Float32 x) override { _position.set_x(x); }

        virtual inline Float32 get_y() const override { return _position.get_y(); }
        virtual inline void set_y(const Float32 y) override { _position.set_y(y); }
    };
}