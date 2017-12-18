#pragma once

#include "../ZeroEngineStd.h"
#include "EventType.h"
#include "EventData.h"
#include "EventListener.h"
#include "../AppLayer/Game.h"

namespace ZeroEngine {

    const uint32_t MAX_MILLISECONDS = 0xffffffff;

    class IEventManager {
    public:
        virtual bool register_listener(const EventListenerDelegate& delegate, const EventType& type) = 0;
        virtual bool unregister_listener(const EventListenerDelegate& delegate, const EventType& type) = 0;
        virtual bool trigger_event(const IEventDataPtr& event_data) const = 0;
        virtual bool queue_event(const IEventDataPtr& event_data) = 0;
        virtual bool abort_event(const EventType& type, bool all=false) = 0;
        virtual bool update(uint32_t max_milliseconds=MAX_MILLISECONDS) = 0;
        virtual const char* get_name() const = 0;
    };

    const uint8_t EVENT_MANAGER_QUEUE_COUNT = 2;

    class BaseEventManager : public IEventManager, public IZeroObject {
    private:
        typedef std::list<EventListenerDelegate> EventListenerList;
        typedef std::map<EventType, EventListenerList> EventListenerMap;
        typedef std::list<IEventDataPtr> EventQueue;
    private:
        const char* _name;
        EventListenerMap _listener_map;
        EventQueue _event_queues[EVENT_MANAGER_QUEUE_COUNT];
        int8_t _active_queue;
    public:
        virtual bool register_listener(const EventListenerDelegate& delegate, const EventType& type) override;
        virtual bool unregister_listener(const EventListenerDelegate& delegate, const EventType& type) override;
        virtual bool trigger_event(const IEventDataPtr& event_data) const override;
        virtual bool abort_event(const EventType& type, bool all=false) override;
        virtual bool queue_event(const IEventDataPtr& event_data) override;
        virtual bool update(uint32_t max_milliseconds=MAX_MILLISECONDS) override;
        inline virtual ~BaseEventManager() {}
        inline virtual StringRepr to_string() const override { return _name; }
        inline const char* get_name() const override { return _name; }
    protected:
        explicit BaseEventManager(const char* name);
    };

    class ZeroEventManager final : public BaseEventManager {
    private:
        inline ZeroEventManager() : BaseEventManager("ZeroEventManager") {};
        static BaseEventManager* _event_manager;
    public:
        static bool register_listener(const EventListenerDelegate& delegate, const EventType& type);
        static bool unregister_listener(const EventListenerDelegate& delegate, const EventType& type);
        static bool trigger_event(const IEventDataPtr& event_data);
        static bool abort_event(const EventType& type, bool all=false);
        static bool queue_event(const IEventDataPtr& event_data);
        static bool update(uint32_t max_milliseconds=MAX_MILLISECONDS);
        static const char* get_name();
        static StringRepr to_string();
        static void shutdown();
        ~ZeroEventManager();
    };

}