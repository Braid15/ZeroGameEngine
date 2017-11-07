#pragma once 

#include "../../ZeroEngineStd.h"
#include "../IMsgTranslator.h"
#include "../../3rdParty/SDL/SDL_events.h"

namespace ZeroEngine {

    class SdlMsgTranslator : public IMsgTranslator {
    private:
        AppMsgType _translation_map[SDL_LASTEVENT];
    public:
        inline SdlMsgTranslator() { init_translation_map(); }
        inline ~SdlMsgTranslator() {}
        AppMsgType translate_message(FrameworkMsgId);
    private:
        void init_translation_map();
    };
} 