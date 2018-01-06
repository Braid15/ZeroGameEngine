#pragma once

#include "../ZeroEngineStd.h"
#include "IScreenElement.h"
#include "../Framework/ITexture.h"
#include "../Math/MathTypes.h"

namespace ZeroEngine {

    class Sprite : public BaseScreenElement {
    private:
        // EntityId or reference to Entity owner
        ITexture* _texture;
        std::string _file_path;
    public:
        Sprite();
        Sprite(std::string file_path);
        virtual ~Sprite();
        virtual bool load();
        virtual bool load(std::string file_path);
        virtual bool render(Tick delta_time) override;

        inline void set_file_path(std::string file_path) { _file_path = file_path; }

        inline const Vector2& get_position() const { return _texture->get_position(); }
        inline void set_position(const Vector2& vec) { _texture->set_position(vec); }

        inline Float32 get_x() const { return _texture->get_x(); }
        inline void set_x(const Float32 x) { _texture->set_x(x); }

        inline Float32 get_y() const { return _texture->get_y(); }
        inline void set_y(const Float32 y) { _texture->set_y(y); }

        inline Float32 get_width() const { return _texture->get_width(); }
        inline void set_width(const Float32 w) { _texture->set_width(w); }

        inline Float32 get_height() const { return _texture->get_height(); }
        inline void set_height(const Float32 h) { _texture->set_height(h); }

        inline StringRepr to_string() const { return "Sprite"; }
    };
}