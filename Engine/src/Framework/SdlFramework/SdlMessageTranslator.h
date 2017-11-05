#pragma once 

#include "../../ZeroEngineStd.h"
#include "../../IMessageTranslator.h"
#include "../../3rdParty/SDL/SDL_events.h"

namespace ZeroEngine {

    class SdlMessageTranslator : public IMessageTranslator {
    private:
        AppMsgType _translation_map[SDL_LASTEVENT];
    public:
        inline SdlMessageTranslator() { init_translation_map(); }
        inline ~SdlMessageTranslator() {}
        AppMsgType translate_message(FrameworkMessageId);
    private:
        void init_translation_map();
    };
} 