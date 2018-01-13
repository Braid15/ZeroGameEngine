#pragma once 

#include "../Engine/src/ZeroEngineStd.h"
#include "../Engine/src/Framework/IMsgTranslator.h"
#include "../Engine/src/Input/Keys.h"
#include "../Engine/src/3rdParty/SDL/SDL_events.h"

namespace ZeroSdlFramework {

    class SdlMsgTranslator : public ZeroEngine::BaseMsgTranslator {
    private:
        SDL_Event _sdl_event;
    public:
        inline SdlMsgTranslator() {}
        inline ~SdlMsgTranslator() {}
        const ZeroEngine::AppMsg* const get_translated_message() override;
        void set_sdl_event_to_translate(const SDL_Event&);
    };
} 