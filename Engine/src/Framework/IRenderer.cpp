#include "IRenderer.h"

namespace ZeroEngine {

    // ---------------------------
    // BaseRenderer Public Members
    // ---------------------------

    void BaseRenderer::set_background_color(uint32 red, uint32 green, uint32 blue, uint32 alpha) {
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

    void BaseRenderer::render_packets() {
        assert(_primitive_renderer);
        // @TEMP: Optimize performance if needed. MIght need to use two
        // lists so that there is a back-buffer where packets can be submitted
        // whjile the other is being rendered
        for (auto packet : _render_packets) {
            packet->on_render(*_primitive_renderer);
        }
        // _render_packets.clear();
    }

    void BaseRenderer::submit_packet(IRenderPacket::s_ptr packet) {
        _render_packets.push_back(packet);
    }

    void BaseRenderer::remove_packet(IRenderPacket::s_ptr packet) {
        RenderPacketList::iterator iter;
        bool found = false;
        for (iter = _render_packets.begin(); iter != _render_packets.end(); ++iter) {
            if (*iter == packet) {
                found = true;
                break;
            }
        }

        if (found) {
            _render_packets.remove(packet);
        } else {
            LOG_DEBUG("BaseRenderer", "Packet not found for removal");
        }
    }

    // -------------------------------
    // BaseRenderer Protected Members
    // -------------------------------

    void BaseRenderer::set_primitive_renderer(IPrimitiveRenderer* renderer) {
        assert(renderer);
        if (_primitive_renderer) {
            zero_delete(_primitive_renderer);
        }
        _primitive_renderer = renderer;
    }

    IPrimitiveRenderer* BaseRenderer::get_primitive_renderer() const {
        assert(_primitive_renderer);
        return _primitive_renderer;
    }
}