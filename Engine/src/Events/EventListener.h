#pragma once 

#include "../ZeroEngineStd.h"
#include "EventData.h"
#include "../3rdParty/FastDelegate/FastDelegate.h"

namespace ZeroEngine {

    // Need this forward dec
    class IEventData;

    typedef std::shared_ptr<IEventData> IEventDataPtr;
    typedef fastdelegate::FastDelegate1<IEventDataPtr> EventListenerDelegate;
}