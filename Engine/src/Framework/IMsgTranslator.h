#pragma once 

#include "../ZeroEngineStd.h"
#include "../AppMsg/AppMsgFactory.h"
#include "../AppMsg/AppMsg.h"

namespace ZeroEngine {

    class IMsgTranslator {
    public:
        virtual const AppMsg* const get_translated_message() = 0;
    };

    // @TODO: Put in seperate file
    class BaseMsgTranslator : public IMsgTranslator {
    protected:
        AppMsgFactory* _factory;
    public:
        inline virtual ~BaseMsgTranslator() { zero_delete(_factory); }
        virtual const AppMsg* const get_translated_message() = 0;
    protected:
        inline BaseMsgTranslator() { _factory = zero_new AppMsgFactory(); }
    };
}