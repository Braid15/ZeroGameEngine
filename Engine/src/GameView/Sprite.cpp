#include "Sprite.h"
#include "../AppLayer/Game.h"

namespace ZeroEngine {

    Sprite::Sprite() {
        _texture = nullptr;
    }

    Sprite::Sprite(std::string file_path) {
        _texture = nullptr;
        _file_path = file_path;
    }

    Sprite::~Sprite() {
        zero_delete(_texture);
    }

    bool Sprite::load() {
        if (_file_path.empty() || _texture) return false;

        assert(Game::get_renderer());
        _texture = Game::get_renderer()->create_texture(_file_path.c_str());

        return (_texture != nullptr && _texture->load());
    }

    bool Sprite::load(std::string file_path) {
        // Already loaded
        if (_texture) return false;

        _file_path = file_path;
        assert(Game::get_renderer());
        _texture = Game::get_renderer()->create_texture(_file_path.c_str());
        return (_texture != nullptr && _texture->load());
    }

    bool Sprite::render(Tick delta_time) {
        if (!is_visible() || !_texture) return false;

        _texture->on_render();
        return true;
    }
}