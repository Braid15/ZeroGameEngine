#include "IRenderer.h"

namespace ZeroEngine {

    void BaseRenderer::set_background_color(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha) {
        _background_color.set_red(red);
        _background_color.set_green(green);
        _background_color.set_blue(blue);
        _background_color.set_alpha(alpha);
    }

    void BaseRenderer::set_background_color(const Color& color) {
        _background_color.set_red(color.get_red());
        _background_color.set_green(color.get_green());
        _background_color.set_blue(color.get_blue());
        _background_color.set_alpha(color.get_alpha());
    }
}