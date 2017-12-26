#pragma once

#include "../ZeroEngineStd.h"
#include "IScreenElement.h"
#include "../Framework/ITexture.h"

namespace ZeroEngine {

    class Sprite : public BaseScreenElement {
    private:
        // EntityId or reference to Entity owner
        ITexture* _texture;
        char* _file_path;
    public:
        Sprite();
        Sprite(char* file_path);
        virtual ~Sprite();
        virtual bool load();
        virtual bool load(char* file_path);
        virtual bool render(Tick delta_time) override;

        inline void set_file_path(char* file_path) { _file_path = file_path; }

        inline int32_t get_x() const { return _texture->get_x(); }
        inline void set_x(const int32_t x) { _texture->set_x(x); }

        inline int32_t get_y() const { return _texture->get_y(); }
        inline void set_y(const int32_t y) { _texture->set_y(y); }

        inline uint32_t get_width() const { return _texture->get_width(); }
        inline void set_width(const uint32_t w) { _texture->set_width(w); }

        inline uint32_t get_height() const { return _texture->get_height(); }
        inline void set_height(const uint32_t h) { _texture->set_height(h); }
    };
}