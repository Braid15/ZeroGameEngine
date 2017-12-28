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
#include "SdlRenderer.h"

namespace ZeroEngine {

    class SdlMsgTranslator;

    class SdlFramework : public AFramework {
        SDL_Window* _sdl_window;
        SDL_Event _event;
        SdlMsgTranslator* _msg_translator;

    public:
        inline SdlFramework() : _sdl_window(nullptr), _msg_translator(nullptr) {}
        inline ~SdlFramework() { zero_delete(_msg_translator); }

    public:
        BaseRenderer::s_ptr create_renderer() override;
        IWindow::ptr create_window(std::string title, Point<int32> size) override;
        bool on_init() override;
        bool on_shutdown() override;
        void process_input() override;
        Tick get_current_time() const override;
        inline StringRepr to_string() const override { return "SdlFramework"; }
    };
}


