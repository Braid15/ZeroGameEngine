#include "RenderPacketTypes.h"

namespace ZeroEngine {

    void LineRenderPacket::on_render(IRenderer& renderer) {
        renderer.draw_line(_start, _end, get_color());
    }
}