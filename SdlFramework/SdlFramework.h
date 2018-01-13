#pragma once


#include "../Engine/src/ZeroEngineStd.h"
#include "../Engine/src/Graphics/Point.h"
#include "../Engine/src/Time.h"
#include "../Engine/src/AppMsg/AppMsg.h"
#include "../Engine/src/Framework/AFramework.h"
#include "../Engine/src/3rdParty/SDL/SDL.h"
#include "../Engine/src//3rdParty/SDL/SDL_syswm.h"
#include "../Engine/src/3rdParty/SDL/SDL_image.h"
#include "../Engine/src/3rdParty/SDL/SDL_mixer.h"
#include "../Engine/src/3rdParty/SDL/SDL_ttf.h"
#include "SdlMsgTranslator.h"
#include "SdlRenderer.h"

namespace ZeroSdlFramework {

    class SdlMsgTranslator;

    class SdlFramework : public ZeroEngine::AFramework {
        SDL_Window* _sdl_window;
        SDL_Event _event;
        SdlMsgTranslator* _msg_translator;

    public:
        inline SdlFramework() : _sdl_window(nullptr), _msg_translator(nullptr) {}
        inline ~SdlFramework() { zero_delete(_msg_translator); }

    public:
        ZeroEngine::BaseRenderer::s_ptr create_renderer() override;
        ZeroEngine::IWindow::ptr create_window(std::string title, ZeroEngine::Point<ZeroEngine::Int32> size) override;
        bool on_init() override;
        bool on_shutdown() override;
        void process_input() override;
        ZeroEngine::Tick get_current_time() const override;
        inline ZeroEngine::StringRepr to_string() const override { return "SdlFramework"; }
    };
}


