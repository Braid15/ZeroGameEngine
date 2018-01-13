#pragma once

#include "../Engine/src/ZeroEngineStd.h"
#include "../Engine/src/Framework/ITexture.h"
#include "../Engine/src/3rdParty/SDL/SDL.h"
#include "../Engine/src/3rdParty/SDL/SDL_image.h"

namespace ZeroSdlFramework {

    class SdlTexture final : public ZeroEngine::BaseTexture {
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
        inline ZeroEngine::StringRepr to_string() const { return "SdlTexture"; }
    private:
        SdlTexture() : _renderer(nullptr), _texture(nullptr), _window(nullptr), _file_path(nullptr) {}
        SdlTexture(const SdlTexture&) : _renderer(nullptr), _texture(nullptr), 
            _window(nullptr), _file_path(nullptr) {}
    };
}