#pragma once

#include "../ZeroEngineStd.h"
#include "../Graphics/Graphics.h"
#include "../Rendering/IRenderPacket.h"
#include "../Rendering/IPrimitiveRenderer.h"

// @TODO: Move this and cpp file to Rendering folder
// @TODO: Make seperate file for BaseRenderer

namespace ZeroEngine {

    class ITexture;

    class IRenderer : public IZeroObject {
    public:
        virtual void set_background_color(Uint32 red,
                                          Uint32 green, 
                                          Uint32 blue, 
                                          Uint32 alpha
        ) = 0;
        virtual void set_background_color(const Color& color) = 0;
        virtual bool pre_render() = 0;
        virtual bool post_render() = 0;
        virtual void shutdown() = 0;
        virtual bool on_restore() = 0;
        // @TODO: I want to factor out primitive drawing into a seperate interface
        virtual void draw_line(const Point<Int32>& from, const Point<Int32>& to, const Color& color) = 0;
        virtual void render_packets() = 0;
        virtual void submit_packet(IRenderPacket::s_ptr) = 0;
        virtual void remove_packet(IRenderPacket::s_ptr) = 0;
        virtual StringRepr to_string() const = 0;
        // @TODO: Seperate interface??
        virtual ITexture* create_texture(const char* file_path) = 0;
        inline virtual ~IRenderer() {}
        typedef std::shared_ptr<IRenderer> s_ptr;
    };

    // IRenderer implementations need to subclass this class because it exposes
    // a different interface which is necessary for AFramework to access
    class BaseRenderer : public IRenderer {
    private:
        Color _background_color;
        typedef std::list<IRenderPacket::s_ptr> RenderPacketList;
        RenderPacketList _render_packets;

        // Use naked ptr since this will be the only class and
        // sub-classes are the only ones with access to it.
        IPrimitiveRenderer* _primitive_renderer;
    public:
        inline BaseRenderer() : _primitive_renderer(nullptr) {}
        virtual ~BaseRenderer() { zero_delete(_primitive_renderer); }
        virtual void set_background_color(Uint32 red, Uint32 green, Uint32 blue, Uint32 alpha) override;
        virtual void set_background_color(const Color& color) override;
        virtual bool pre_render() = 0;
        virtual bool post_render() = 0;
        virtual void shutdown() = 0;
        virtual bool on_restore() = 0;
        virtual void draw_line(const Point<Int32>& from, const Point<Int32>& to, const Color& color) = 0;
        virtual void render_present() = 0;
        virtual void render_packets(); 
        virtual ITexture* create_texture(const char* file_path) = 0;
        virtual void submit_packet(IRenderPacket::s_ptr);
        virtual void remove_packet(IRenderPacket::s_ptr);
        virtual StringRepr to_string() const = 0;
        typedef std::shared_ptr<BaseRenderer> s_ptr;
    protected:
        void set_primitive_renderer(IPrimitiveRenderer*);
        IPrimitiveRenderer* get_primitive_renderer() const;

        const Color& get_background_color() const { return _background_color; }
    };

    class NullRenderer final : public BaseRenderer {
    public:
        inline void shutdown() override {}
        inline bool on_restore() override { return true; }
        inline bool pre_render() override { return true; }
        inline bool post_render() override { return true; }
        inline void draw_line(const Point<Int32>& from, const Point<Int32>& to, const Color& color) override {}
        inline void render_present() override {}
        inline void render_packets() override {}
        inline void submit_packet(IRenderPacket::s_ptr) override {}
        inline void remove_packet(IRenderPacket::s_ptr) override {}
        inline ITexture* create_texture(const char* file_path) override { return nullptr; }
        inline StringRepr to_string() const override { return "NullRenderer"; }
    };
}