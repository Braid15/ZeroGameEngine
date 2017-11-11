#pragma once 

#include "../../ZeroEngineStd.h"
#include "../IMsgTranslator.h"
#include "../../3rdParty/SDL/SDL_events.h"

namespace ZeroEngine {

    class SdlMsgTranslator : public BaseMsgTranslator {
    private:
        AppMsgType _translation_map[SDL_LASTEVENT];
        SDL_Event _sdl_event_to_translate;
    public:
        inline SdlMsgTranslator() { init_translation_map(); }
        inline ~SdlMsgTranslator() { std::cout << "~SdlMsgTranslator\n"; }
        AppMsg& get_translated_message() override;
        void set_sdl_event_to_translate(const SDL_Event&);
    private:
        void init_translation_map();
    };
} 