#pragma once

#include "../ZeroEngineStd.h"
#include "../Graphics/Point.h"
#include "../AppMsg.h"
#include "../AppMsgFactory.h"
#include "../IMessageTranslator.h"
#include "../Time.h"

namespace ZeroEngine {

    class IRenderer;
    class IWindow;
    class IMessageTranslator;

    class AFramework : public IZeroObject {
    public:
        virtual ~AFramework();
        virtual IRenderer* create_renderer() = 0;
        virtual IWindow* create_window(std::string title, Point<long> size) = 0;
        virtual bool initialize() = 0;
        virtual bool shutdown() = 0;
        virtual StringRepr to_string() const = 0;
        inline virtual FrameworkMessageId get_current_message() const { return _current_message; }

    public:
        virtual void main_loop();
        inline void set_update_callback( void (*callback)(Time) ) { _update_callback = callback; }
        inline void set_render_callback( void (*callback)(Time) ) { _render_callback = callback; }
        inline void set_app_msg_callback( bool (*callback)(AppMsg&) ) { _app_msg_callback = callback; }

    protected:
        AFramework();
        //inline AFramework(): _current_message( new AppMsg( 0 ) ) {}
        virtual bool dispatch_message() = 0;
        virtual void frame_begin(Time delta_time) = 0;
        virtual void frame_render(Time delta_time) = 0;
        inline virtual void frame_end(Time delta_time) {}
        AppMsgFactory* _message_factory;
        IMessageTranslator* _message_translator;
        bool _is_running;
        FrameworkMessageId _current_message;

    //private:
    // TEMPORARY: I want these private I think
    protected:
        void (*_render_callback)( Time time );
        void (*_update_callback)( Time time );
        bool (*_app_msg_callback)( AppMsg& msg );
    };
}

