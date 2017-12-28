#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Graphics/Point.h"
#include "../AppMsg/AppMsg.h"
#include "../AppMsg/AppMsgFactory.h"
#include "../Input//Keyboard.h"
#include "../Input/Mouse.h"
#include "IMsgTranslator.h"
#include "IRenderer.h"
#include "IWindow.h"

namespace ZeroEngine {

    class IMsgTranslator;

    class AFramework : public IZeroObject {
    public:
        virtual ~AFramework();
        bool initialize();
        bool shutdown();
        bool initialize_window_and_renderer(std::string title, Point<int32> size);
        virtual StringRepr to_string() const = 0;
        virtual Tick get_current_time() const = 0;
        virtual void run_main_loop();
        inline void set_update_callback(void (*callback)(Tick)) { _update_callback = callback; }
        inline void set_render_callback(void (*callback)(Tick)) { _render_callback = callback; }
        inline void set_app_msg_callback(bool (*callback)(AppMsg::ptr)) { _app_msg_callback = callback; }
        // Important that this returns IRenderer and not BaseRenderer since BaseRenderer's public interface
        // is only meant for AFramework
        inline IRenderer::s_ptr get_renderer() const { return _renderer; }
    protected:
        AFramework();
        void set_app_msg_translator(IMsgTranslator*);
        virtual void process_input() = 0;
        void dispatch_message();
        virtual bool on_init() = 0;
        virtual bool on_shutdown() = 0;
        virtual BaseRenderer::s_ptr create_renderer() = 0;
        virtual IWindow::ptr create_window(std::string title, Point<int32> size) = 0;
    private:
        bool _is_running;
        AppMsgFactory* _msg_factory;
        IMsgTranslator* _msg_translator;
        BaseRenderer::s_ptr _renderer;
        IWindow::ptr _window;

    //private:
    // TEMPORARY: I want these private I think
    protected:
        void (*_render_callback)( Tick time );
        void (*_update_callback)(Tick time);
        bool (*_app_msg_callback)(AppMsg::ptr msg);
    };
}