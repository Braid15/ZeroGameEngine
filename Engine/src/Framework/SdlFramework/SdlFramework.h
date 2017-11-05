#pragma once

#include "../../ZeroEngineStd.h"
#include "../../Graphics/Point.h"
#include "../../Time.h"
#include "../../AppMsg.h"
#include "../AFramework.h"
#include "SdlMessageTranslator.h"
#include "../../3rdParty/SDL/SDL.h"
#include "../../3rdParty/SDL/SDL_syswm.h"
#include "../../3rdParty/SDL/SDL_image.h"
#include "../../3rdParty/SDL/SDL_mixer.h"
#include "../../3rdParty/SDL/SDL_ttf.h"

namespace ZeroEngine {

    class SdlMessageTranslator;

    class SdlFramework : public AFramework {
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        SDL_Event _event;

    public:
        inline SdlFramework(): _window(nullptr), _renderer(nullptr) {}
        inline ~SdlFramework() {}

    public:
        IRenderer* create_renderer();
        IWindow* create_window(std::string title, Point<long> size);
        bool on_init();
        bool on_shutdown();
        void poll_message();
        Time get_current_time() const;
        void frame_render_present(Time delta_time);
        inline StringRepr to_string() const { return "SdlFramework"; }
    };
}


