#include "stdafx.h"
#include "SdlTexture.h"
#include "../Engine/src/Logger/Logging.h"
#include "../Engine/src/Math/Math.h"

namespace ZeroSdlFramework {

    using namespace ZeroEngine;

    SdlTexture::SdlTexture(SDL_Renderer* renderer, SDL_Window* window, const char* file_path) {
        _renderer = renderer;
        _texture = nullptr;
        _file_path = file_path;
        _window = window;
    }

    SdlTexture::~SdlTexture() {
        // Do not destroy _renderer or _window!!
        if (_texture) {
            SDL_DestroyTexture(_texture);
        }
        _texture = nullptr;
    }

    bool SdlTexture::load() {
        if (!_file_path || _texture || !_renderer) return false;

        SDL_Surface* surface = IMG_Load(_file_path);
        bool success = false;
        if (surface) {
            _texture = SDL_CreateTextureFromSurface(_renderer, surface);
            if (_texture) {
                set_width(static_cast<Float32>(surface->w));
                set_height(static_cast<Float32>(surface->h));
                SDL_FreeSurface(surface);
                success = true;
            } else {
                LOG_DEBUG("SdlTexture", SDL_GetError());
            }
        } else {
            LOG_DEBUG("SdlTexture", SDL_GetError());
        }

        return success;
    }

    void SdlTexture::on_render() {
        if (!_renderer || !_texture) return;

        SDL_Rect render_quad = { static_cast<Int32>(get_x()), static_cast<Int32>(get_y()), static_cast<Int32>(get_width()), static_cast<Int32>(get_height()) };
        LOG_TODO("SdlTexture", "Need to handle source rect and dest rect. I.E. Sprite sheets");
        SDL_RenderCopy(_renderer, _texture, nullptr, &render_quad);
    }
}