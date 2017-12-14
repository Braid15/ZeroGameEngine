#pragma once

#include "../../ZeroEngineStd.h"
#include "../../Graphics/Point.h"
#include "../../Time.h"
#include "../../AppMsg/AppMsg.h"
#include "../AFramework.h"
#include "../../3rdParty/SDL/SDL.h"
#include "../../3rdParty/SDL/SDL_syswm.h"
#include "../../3rdParty/SDL/SDL_image.h"
#include "../../3rdParty/SDL/SDL_mixer.h"
#include "../../3rdParty/SDL/SDL_ttf.h"
#include "SdlMsgTranslator.h"

namespace ZeroEngine {

    class SdlMsgTranslator;

    class SdlFramework : public AFramework {
        SDL_Window* _window;
        SDL_Renderer* _renderer;
        SDL_Event _event;
        SdlMsgTranslator* _msg_translator;

    public:
        inline SdlFramework(): _window(nullptr), _renderer(nullptr), _msg_translator(nullptr) {}
        inline ~SdlFramework() { zero_delete(_msg_translator); }

    public:
        IRenderer* create_renderer();
        IWindow* create_window(std::string title, Point<long> size);
        bool on_init();
        bool on_shutdown();
        void process_input();
        Tick get_current_time() const;
        void frame_render_present(Tick delta_time);
        inline StringRepr to_string() const { return "SdlFramework"; }
    };
}


