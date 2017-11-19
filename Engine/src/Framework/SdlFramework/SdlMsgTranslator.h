#pragma once 

#include "../../ZeroEngineStd.h"
#include "../IMsgTranslator.h"
#include "../../Input/Keys.h"
#include "../../3rdParty/SDL/SDL_events.h"

namespace ZeroEngine {

    class SdlMsgTranslator : public BaseMsgTranslator {
    private:
        SDL_Event _sdl_event;
    public:
        inline SdlMsgTranslator() {}
        inline ~SdlMsgTranslator() {}
        const AppMsg* const get_translated_message() override;
        void set_sdl_event_to_translate(const SDL_Event&);
    };
} 