#pragma once

#include "../../ZeroEngineStd.h"
#include "../ITexture.h"
#include "../../3rdParty/SDL/SDL.h"
#include "../../3rdParty/SDL/SDL_image.h"

namespace ZeroEngine {

    class SdlTexture final : public BaseTexture {
    private:
        SDL_Renderer* _renderer;
        SDL_Texture* _texture;
        SDL_Window* _window;
        const char* _file_path;
    public:
        SdlTexture(SDL_Renderer*, SDL_Window*, const char* file_path);
        ~SdlTexture();
        bool load() override;
        void on_render() override;
        inline StringRepr to_string() const { return "SdlTexture"; }
    private:
        SdlTexture() : _renderer(nullptr), _texture(nullptr), _window(nullptr), _file_path(nullptr) {}
        SdlTexture(const SdlTexture&) : _renderer(nullptr), _texture(nullptr), 
            _window(nullptr), _file_path(nullptr) {}
    };
}