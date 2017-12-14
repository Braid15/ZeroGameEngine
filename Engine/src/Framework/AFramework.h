#pragma once

#include "../ZeroEngineStd.h"
#include "../Time.h"
#include "../Graphics/Point.h"
#include "../AppMsg/AppMsg.h"
#include "../AppMsg/AppMsgFactory.h"
#include "../Input//Keyboard.h"
#include "../Input/Mouse.h"
#include "IMsgTranslator.h"

namespace ZeroEngine {

    class IRenderer;
    class IWindow;
    class IMsgTranslator;

    class AFramework : public IZeroObject {
    public:
        virtual ~AFramework();
        virtual IRenderer* create_renderer() = 0;
        virtual IWindow* create_window(std::string title, Point<long> size) = 0;
        bool initialize();
        bool shutdown();
        virtual StringRepr to_string() const = 0;
        virtual Tick get_current_time() const = 0;
        virtual void run_main_loop();
        inline void set_update_callback(void (*callback)(Tick)) { _update_callback = callback; }
        inline void set_render_callback(void (*callback)(Tick)) { _render_callback = callback; }
        inline void set_app_msg_callback(bool (*callback)(const AppMsg* const)) { _app_msg_callback = callback; }
    protected:
        AFramework();
        void set_app_msg_translator(IMsgTranslator*);
        virtual void process_input() = 0;
        void dispatch_message();
        inline virtual void frame_render_begin(Tick delta_time) {}
        virtual void frame_render_present(Tick delta_time) = 0;
        inline virtual void frame_render_end(Tick delta_time) {}
        virtual bool on_init() = 0;
        virtual bool on_shutdown() = 0;
    private:
        bool _is_running;
        AppMsgFactory* _msg_factory;
        IMsgTranslator* _msg_translator;

    //private:
    // TEMPORARY: I want these private I think
    protected:
        void (*_render_callback)( Tick time );
        void (*_update_callback)(Tick time);
        bool (*_app_msg_callback)(const AppMsg* const msg);
    };
}

